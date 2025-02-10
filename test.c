#include <stdio.h>
#include <math.h>
#include "lib.h"

void test_matmul() {
    int n = 2;
    int m = 2;
    int x = 2;
    float matrix_a[2][2] = {{1, 2}, {3, 4}};
    float matrix_b[2][2] = {{5, 6}, {7, 8}};
    float result[2][2] = {{0, 0}, {0, 0}};

    printf("Matrix A:\n");
    print_matrix(n, m, matrix_a);

    printf("\nMatrix B:\n");
    print_matrix(n, m, matrix_b);

    printf("\nExecute matmul...\n");
    matmul(n, m, x, matrix_a, matrix_b, result);

    printf("\nResult Matrix:\n");
    print_matrix(n, m, result);

    // Expected result should be:
    // [19 22]
    // [43 50]
    printf("\nChecking result...\n");
    if (result[0][0] == 19 && result[0][1] == 22 && 
        result[1][0] == 43 && result[1][1] == 50) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
        printf("Expected:\n19 22\n43 50\n");
        printf("Got:\n%.0f %.0f\n%.0f %.0f\n", 
               result[0][0], result[0][1],
               result[1][0], result[1][1]);
    }
}

void test_transpose() {
    int n = 2;
    int m = 3;
    float matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
    float result[3][2] = {{0, 0}, {0, 0}, {0, 0}};

    printf("\n=== Testing transpose ===\n");
    printf("Original Matrix:\n");
    print_matrix(n, m, matrix);

    printf("\nExecute transpose...\n");
    transpose(n, m, matrix, result);

    printf("\nTransposed Matrix:\n");
    print_matrix(m, n, result);

    // Expected result should be:
    // [1 4]
    // [2 5]
    // [3 6]
    printf("\nChecking result...\n");
    if (result[0][0] == 1 && result[0][1] == 4 &&
        result[1][0] == 2 && result[1][1] == 5 &&
        result[2][0] == 3 && result[2][1] == 6) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
        printf("Expected:\n1 4\n2 5\n3 6\n");
        printf("Got:\n%.0f %.0f\n%.0f %.0f\n%.0f %.0f\n",
               result[0][0], result[0][1],
               result[1][0], result[1][1],
               result[2][0], result[2][1]);
    }
}

void test_softmax() {
    int n = 2;
    int m = 2;
    float matrix[2][2] = {{1, 2}, {3, 4}};
    float result[2][2] = {{0, 0}, {0, 0}};

    printf("\n=== Testing softmax ===\n");
    printf("Original Matrix:\n");
    print_matrix(n, m, matrix);

    printf("\nExecute softmax...\n");
    softmax(n, m, matrix, result);

    printf("\nSoftmax Result:\n");
    print_matrix(n, m, result);

    // Expected results (rounded to 2 decimal places):
    // [0.27 0.73]
    // [0.27 0.73]
    printf("\nChecking result...\n");
    if (fabs(result[0][0] - 0.27) < 0.01 && fabs(result[0][1] - 0.73) < 0.01 &&
        fabs(result[1][0] - 0.27) < 0.01 && fabs(result[1][1] - 0.73) < 0.01) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
        printf("Expected:\n0.27 0.73\n0.27 0.73\n");
        printf("Got:\n%.2f %.2f\n%.2f %.2f\n",
               result[0][0], result[0][1],
               result[1][0], result[1][1]);
    }
}

int main() {
    test_matmul();
    test_transpose();
    test_softmax();
    return 0;
}
