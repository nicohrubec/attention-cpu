#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>

void print_matrix(int n, uint8_t (*matrix)[n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void init_matrix(int n, uint8_t (*matrix)[n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 2;
        }
    }
}

int main(int argc, char *argv[]) {
    int seed = 42;
    int n = 10;
    int verbose = 0;
    int opt;

    // define arguments
    static struct option long_options[] = {{"number", required_argument, 0, 'n'},
                                           {"seed", required_argument, 0, 's'},
                                           {"verbose", no_argument, 0, 'v'},
                                           {0, 0, 0, 0}};
    
    // argument parsing
    while (1) {
        int option_index = 0;
        opt = getopt_long(argc, argv, "n:g:s:d:v", long_options, &option_index);

        if (opt == -1) break;

        switch (opt) {
            case 'n':
                n = atoi(optarg);
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

    uint8_t(*input_matrix)[n];
    input_matrix = (uint8_t(*)[n])malloc(n * n * sizeof(uint8_t));
    init_matrix(n, input_matrix);

    if (verbose) {
        printf("Input matrix:\n");
        print_matrix(n, input_matrix);
    }

    // clean up
    free(input_matrix);
    return 0;
}