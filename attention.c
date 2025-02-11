#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "lib.h"

// attention:
// step 1: multiply input matrix with keys, values, and queries
// step 2: multiply queries with transposed keys
// step 3: divide by sqrt(model_dim)
// step 4: apply softmax
// step 5: multiply with values
void attention(int seq_len, int embedding_dim, int d_model, float (*input_matrix)[embedding_dim], 
                float (*pretrained_queries_matrix)[d_model], float (*pretrained_keys_matrix)[d_model],
                float (*pretrained_values_matrix)[d_model], float (*output_matrix)[d_model]) {
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    
    // project input matrix with keys, values, and queries
    // seq_len * d_model
    float (*queries_matrix)[d_model];
    queries_matrix = (float(*)[d_model])malloc(seq_len * d_model * sizeof(float));
    matmul(seq_len, embedding_dim, d_model, input_matrix, pretrained_keys_matrix, queries_matrix);

    // seq_len * d_model
    float (*keys_matrix)[d_model];
    keys_matrix = (float(*)[d_model])malloc(seq_len * d_model * sizeof(float));
    matmul(seq_len, embedding_dim, d_model, pretrained_queries_matrix, pretrained_keys_matrix, keys_matrix);

    // seq_len * d_model
    float (*values_matrix)[d_model];
    values_matrix = (float(*)[d_model])malloc(seq_len * d_model * sizeof(float));
    matmul(seq_len, embedding_dim, d_model, pretrained_queries_matrix, pretrained_values_matrix, values_matrix);

    // transpose keys matrix: d_model * seq_len
    float (*transposed_keys_matrix)[seq_len];
    transposed_keys_matrix = (float(*)[seq_len])malloc(d_model * seq_len * sizeof(float));
    transpose(d_model, seq_len, keys_matrix, transposed_keys_matrix);

    // calculate how much each word pays attention to each other word: seq_len * seq_len
    float (*attention_matrix)[seq_len];
    attention_matrix = (float(*)[seq_len])malloc(seq_len * seq_len * sizeof(float));
    matmul(seq_len, d_model, seq_len, queries_matrix, transposed_keys_matrix, attention_matrix);
    scale(seq_len, seq_len, attention_matrix, 1 / sqrt(d_model));
    softmax(seq_len, seq_len, attention_matrix);

    // multiply with values: seq_len * d_model
    matmul(seq_len, seq_len, d_model, attention_matrix, values_matrix, output_matrix);

    gettimeofday(&end_time, NULL);
    double time_taken = (end_time.tv_sec - start_time.tv_sec) + 
                       (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("Time taken: %f seconds\n", time_taken);

    // clean up temporary matrices
    free(queries_matrix);
    free(keys_matrix);
    free(values_matrix);
    free(transposed_keys_matrix);
    free(attention_matrix);
}

// a faster version of the above attention implementation
void fast_attention(int seq_len, int embedding_dim, int d_model, float (*input_matrix)[embedding_dim], 
                    float (*pretrained_queries_matrix)[d_model], float (*pretrained_keys_matrix)[d_model],
                    float (*pretrained_values_matrix)[d_model], float (*output_matrix)[d_model]) {
    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);
    
    // project input matrix with keys, values, and queries
    // seq_len * d_model
    float (*queries_matrix)[d_model];
    queries_matrix = (float(*)[d_model])malloc(seq_len * d_model * sizeof(float));
    fast_matmul(seq_len, embedding_dim, d_model, input_matrix, pretrained_keys_matrix, queries_matrix);

    // seq_len * d_model
    float (*keys_matrix)[d_model];
    keys_matrix = (float(*)[d_model])malloc(seq_len * d_model * sizeof(float));
    fast_matmul(seq_len, embedding_dim, d_model, pretrained_queries_matrix, pretrained_keys_matrix, keys_matrix);

    // seq_len * d_model
    float (*values_matrix)[d_model];
    values_matrix = (float(*)[d_model])malloc(seq_len * d_model * sizeof(float));
    fast_matmul(seq_len, embedding_dim, d_model, pretrained_queries_matrix, pretrained_values_matrix, values_matrix);

    // transpose keys matrix: d_model * seq_len
    float (*transposed_keys_matrix)[seq_len];
    transposed_keys_matrix = (float(*)[seq_len])malloc(d_model * seq_len * sizeof(float));
    transpose(d_model, seq_len, keys_matrix, transposed_keys_matrix);

    // calculate how much each word pays attention to each other word: seq_len * seq_len
    float (*attention_matrix)[seq_len];
    attention_matrix = (float(*)[seq_len])malloc(seq_len * seq_len * sizeof(float));
    fast_matmul(seq_len, d_model, seq_len, queries_matrix, transposed_keys_matrix, attention_matrix);
    scale(seq_len, seq_len, attention_matrix, 1 / sqrt(d_model));
    softmax(seq_len, seq_len, attention_matrix);

    // multiply with values: seq_len * d_model
    fast_matmul(seq_len, seq_len, d_model, attention_matrix, values_matrix, output_matrix);

    gettimeofday(&end_time, NULL);
    double time_taken = (end_time.tv_sec - start_time.tv_sec) + 
                       (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("Time taken: %f seconds\n", time_taken);

    // clean up temporary matrices
    free(queries_matrix);
    free(keys_matrix);
    free(values_matrix);
    free(transposed_keys_matrix);
    free(attention_matrix);
}

int main(int argc, char *argv[]) {
    int seed = 42;
    int seq_len = 2048;
    int d_model = 512;
    int embedding_dim = 512;
    int verify = 0;
    int opt;

    // define arguments
    static struct option long_options[] = {{"seq_len", required_argument, 0, 'n'},
                                           {"d_model", required_argument, 0, 'd'},
                                           {"embedding_dim", required_argument, 0, 'e'},
                                           {"seed", required_argument, 0, 's'},
                                           {"verify", no_argument, 0, 'v'},
                                           {0, 0, 0, 0}};
    
    // argument parsing
    while (1) {
        int option_index = 0;
        opt = getopt_long(argc, argv, "n:s:d:e:v", long_options, &option_index);

        if (opt == -1) break;

        switch (opt) {
            case 'n':
                seq_len = atoi(optarg);
                break;
            case 'd':
                d_model = atoi(optarg);
                break;
            case 'e':
                embedding_dim = atoi(optarg);
                break;
            case 's':
                seed = atoi(optarg);
                break;
            case 'v':
                verify = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s -n <n> -s <s> -v\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    srand(seed);

    // input matrix: seq_len * embedding_dim
    float(*input_matrix)[embedding_dim];
    input_matrix = (float(*)[embedding_dim])malloc(seq_len * embedding_dim * sizeof(float));
    init_matrix(seq_len, embedding_dim, input_matrix);

    // queries matrix: embedding_dim * d_model
    float(*pretrained_queries_matrix)[d_model];
    pretrained_queries_matrix = (float(*)[d_model])malloc(embedding_dim * d_model * sizeof(float));
    init_matrix(embedding_dim, d_model, pretrained_queries_matrix);

    // keys matrix: embedding_dim * d_model
    float(*pretrained_keys_matrix)[d_model];
    pretrained_keys_matrix = (float(*)[d_model])malloc(embedding_dim * d_model * sizeof(float));
    init_matrix(embedding_dim, d_model, pretrained_keys_matrix);

    // values matrix: embedding_dim * d_model
    float(*pretrained_values_matrix)[d_model];
    pretrained_values_matrix = (float(*)[d_model])malloc(embedding_dim * d_model * sizeof(float));
    init_matrix(embedding_dim, d_model, pretrained_values_matrix);

    printf("Running fast attention...\n");
    float(*output_matrix_fast_attention)[d_model];
    output_matrix_fast_attention = (float(*)[d_model])malloc(seq_len * d_model * sizeof(float));
    fast_attention(seq_len, embedding_dim, d_model, input_matrix, pretrained_queries_matrix, pretrained_keys_matrix, pretrained_values_matrix, output_matrix_fast_attention);

    // verify
    if (verify) {
        printf("Running slow attention...\n");
        float(*output_matrix_slow_attention)[d_model];
        output_matrix_slow_attention = (float(*)[d_model])malloc(seq_len * d_model * sizeof(float));
        attention(seq_len, embedding_dim, d_model, input_matrix, pretrained_queries_matrix, pretrained_keys_matrix, pretrained_values_matrix, output_matrix_slow_attention);

        if (is_equal(seq_len, d_model, output_matrix_slow_attention, output_matrix_fast_attention)) {
            printf("VERIFICATION PASSED\n");
        } else {
            printf("VERIFICATION FAILED\n");
        }
        
        free(output_matrix_slow_attention);
    }

    // clean up
    free(input_matrix);
    free(pretrained_queries_matrix);
    free(pretrained_keys_matrix);
    free(pretrained_values_matrix);
    free(output_matrix_fast_attention);
    return 0;
}