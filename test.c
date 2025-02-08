#include <stdio.h>

#include "lib.h"

void test_matmul() {
    int n = 2;
    int m = 2;
    float matrix_a[2][2] = {{1, 2}, {3, 4}};
    float matrix_b[2][2] = {{5, 6}, {7, 8}};
    float result[2][2] = {{0, 0}, {0, 0}};

    printf("Matrix A:\n");
    print_matrix(n, m, matrix_a);

    printf("\nMatrix B:\n");
    print_matrix(n, m, matrix_b);

    printf("\nExecute matmul...\n");
    matmul(n, m, matrix_a, matrix_b, result);

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

int main() {
    test_matmul();
    return 0;
}
