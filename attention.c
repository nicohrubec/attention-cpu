#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <time.h>

void print_matrix(int n, int m, float (*matrix)[n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void init_matrix(int n, int m, float (*matrix)[n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = (float)rand() / RAND_MAX;
        }
    }
}

int main(int argc, char *argv[]) {
    int seed = 42;
    int seq_len = 10;
    int d_model = 10;
    int embedding_dim = 10;
    int verbose = 0;
    int opt;

    // define arguments
    static struct option long_options[] = {{"seq_len", required_argument, 0, 'n'},
                                           {"d_model", required_argument, 0, 'd'},
                                           {"embedding_dim", required_argument, 0, 'e'},
                                           {"seed", required_argument, 0, 's'},
                                           {"verbose", no_argument, 0, 'v'},
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
                verbose = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s -n <n> -s <s> -v\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    srand(seed);

    // input matrix: seq_len * embedding_dim
    float(*input_matrix)[seq_len];
    input_matrix = (float(*)[seq_len])malloc(seq_len * embedding_dim * sizeof(float));
    init_matrix(seq_len, embedding_dim, input_matrix);

    // queries matrix: embedding_dim * d_model
    float(*queries_matrix)[embedding_dim];
    queries_matrix = (float(*)[embedding_dim])malloc(embedding_dim * d_model * sizeof(float));
    init_matrix(embedding_dim, d_model, queries_matrix);

    // keys matrix: embedding_dim * d_model
    float(*keys_matrix)[embedding_dim];
    keys_matrix = (float(*)[embedding_dim])malloc(embedding_dim * d_model * sizeof(float));
    init_matrix(embedding_dim, d_model, keys_matrix);

    // values matrix: embedding_dim * d_model
    float(*values_matrix)[embedding_dim];
    values_matrix = (float(*)[embedding_dim])malloc(embedding_dim * d_model * sizeof(float));
    init_matrix(embedding_dim, d_model, values_matrix);    

    if (verbose) {
        printf("Input matrix:\n");
        print_matrix(seq_len, embedding_dim, input_matrix);

        printf("Queries matrix:\n");
        print_matrix(embedding_dim, d_model, queries_matrix);

        printf("Keys matrix:\n");
        print_matrix(embedding_dim, d_model, keys_matrix);

        printf("Values matrix:\n");
        print_matrix(embedding_dim, d_model, values_matrix);
    }

    clock_t start_time = clock();

    // attention:
    // step 1: multiply input matrix with keys, values, and queries
    // step 2: multiply queries with transposed keys
    // step 3: divide by sqrt(model_dim)
    // step 4: apply softmax
    // step 5: multiply with values
    
    // TODO: implement matrix multiplication
    // TODO: implement softmax
    // TODO: implement transpose

    clock_t end_time = clock();

    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);

    // clean up
    free(input_matrix);
    return 0;
}