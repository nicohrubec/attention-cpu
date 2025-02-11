#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <omp.h>

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
        for (int j = 0; j < x; j++) {
            for (int k = 0; k < m; k++) {
                result[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }   
}

/*
    matrix_a: n * m
    matrix_b: m * x
    result: n * x
*/
void fast_matmul(int n, int m, int x, float (*matrix_a)[m], float (*matrix_b)[x], float (*result)[x]) {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            for (int j = 0; j < x; j++) {
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

void fast_transpose(int n, int m, float (*matrix)[m], float (*result)[n]) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[j][i] = matrix[i][j];
        }
    }
}

void softmax(int n, int m, float (*matrix)[m]) {
    for (int i = 0; i < n; i++) {
        float exp_sum = 0;
        for (int j = 0; j < m; j++) {
            exp_sum += exp(matrix[i][j]);
        }
        for (int j = 0; j < m; j++) {
            matrix[i][j] = exp(matrix[i][j]) / exp_sum;
        }
    }
}

void fast_softmax(int n, int m, float (*matrix)[m]) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        float exp_sum = 0;
        for (int j = 0; j < m; j++) {
            exp_sum += exp(matrix[i][j]);
        }
        for (int j = 0; j < m; j++) {
            matrix[i][j] = exp(matrix[i][j]) / exp_sum;
        }
    }
}

void scale(int n, int m, float (*matrix)[m], float scalar) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] *= scalar;
        }
    }
}

void fast_scale(int n, int m, float (*matrix)[m], float scalar) {
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrix[i][j] *= scalar;
        }
    }
}

int is_equal(int n, int m, float (*matrix_a)[m], float (*matrix_b)[m]) {
    const float epsilon = 1e-6;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (fabs(matrix_a[i][j] - matrix_b[i][j]) > epsilon) {
                return 0;
            }
        }
    }
    return 1;
}