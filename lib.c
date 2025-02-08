#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void print_matrix(int n, int m, float (*matrix)[m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void init_matrix(int n, int m, float (*matrix)[m]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] = (float)rand() / RAND_MAX;
        }
    }
}

/*
    matrix_a: n * m
    matrix_b: m * x
    result: n * x
*/
void matmul(int n, int m, int x, float (*matrix_a)[m], float (*matrix_b)[x], float (*result)[x]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < m; k++) {
                result[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }   
}

void transpose(int n, int m, float (*matrix)[m], float (*result)[n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}
