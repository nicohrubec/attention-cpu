#include <stdio.h>
#include <math.h>
#include "lib.h"

void test_matmul() {
    int n = 2;
    int m = 2;
    int x = 3;
    float matrix_a[2][2] = {{1, 2}, {3, 4}};
    float matrix_b[2][3] = {{5, 6, 7}, {8, 9, 10}};
    float result[2][3] = {{0, 0, 0}, {0, 0, 0}};

    printf("Matrix A:\n");
    print_matrix(n, m, matrix_a);

    printf("\nMatrix B:\n");
    print_matrix(m, x, matrix_b);

    printf("\nExecute matmul...\n");
    matmul(n, m, x, matrix_a, matrix_b, result);

    printf("\nResult Matrix:\n");
    print_matrix(n, x, result);

    // Expected result should be:
    // [21 24 27]
    // [47 54 61]
    printf("\nChecking result...\n");
    if (result[0][0] == 21 && result[0][1] == 24 && result[0][2] == 27 &&
        result[1][0] == 47 && result[1][1] == 54 && result[1][2] == 61) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
        printf("Expected:\n21 24 27\n47 54 61\n");
        printf("Got:\n%.0f %.0f %.0f\n%.0f %.0f %.0f\n",
               result[0][0], result[0][1], result[0][2],
               result[1][0], result[1][1], result[1][2]);
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

    printf("\n=== Testing softmax ===\n");
    printf("Original Matrix:\n");
    print_matrix(n, m, matrix);

    printf("\nExecute softmax...\n");
    softmax(n, m, matrix);

    printf("\nSoftmax Result:\n");
    print_matrix(n, m, matrix);

    // Expected results (rounded to 2 decimal places):
    // [0.27 0.73]
    // [0.27 0.73]
    printf("\nChecking result...\n");
    if (fabs(matrix[0][0] - 0.27) < 0.01 && fabs(matrix[0][1] - 0.73) < 0.01 &&
        fabs(matrix[1][0] - 0.27) < 0.01 && fabs(matrix[1][1] - 0.73) < 0.01) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
        printf("Expected:\n0.27 0.73\n0.27 0.73\n");
        printf("Got:\n%.2f %.2f\n%.2f %.2f\n",
               matrix[0][0], matrix[0][1],
               matrix[1][0], matrix[1][1]);
    }
}

void test_scale() {
    int n = 2;
    int m = 2;
    float matrix[2][2] = {{1, 2}, {3, 4}};
    float scalar = 2;

    printf("\n=== Testing scale ===\n");
    printf("Original Matrix:\n");
    print_matrix(n, m, matrix);

    printf("\nExecute scale...\n");
    scale(n, m, matrix, scalar);

    printf("\nScaled Matrix:\n");
    print_matrix(n, m, matrix);

    // Expected result should be:
    // [2 4]
    // [6 8]
    printf("\nChecking result...\n");
    if (matrix[0][0] == 2 && matrix[0][1] == 4 &&
        matrix[1][0] == 6 && matrix[1][1] == 8) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
        printf("Expected:\n2 4\n6 8\n");
        printf("Got:\n%.0f %.0f\n%.0f %.0f\n",
               matrix[0][0], matrix[0][1],
               matrix[1][0], matrix[1][1]);
    }
}

void test_is_equal() {
    int n = 2;
    int m = 2;
    float matrix_a[2][2] = {{1, 2}, {3, 4}};
    float matrix_b[2][2] = {{1, 2}, {3, 4}};
    float matrix_c[2][2] = {{1, 2}, {3, 5}};

    printf("\n=== Testing is_equal ===\n");
    printf("matrix_a:\n");
    print_matrix(n, m, matrix_a);
    printf("matrix_b:\n");
    print_matrix(n, m, matrix_b);
    printf("matrix_c:\n");
    print_matrix(n, m, matrix_c);

    printf("\nChecking matrix_a and matrix_b...\n");

    if (is_equal(n, m, matrix_a, matrix_b)) {
        printf("PASS: matrix_a and matrix_b are equal\n");
    } else {
        printf("FAIL: matrix_a and matrix_b are not equal\n");
    }

    printf("\nChecking matrix_a and matrix_c...\n");

    if (!is_equal(n, m, matrix_a, matrix_c)) {
        printf("PASS: matrix_a and matrix_c are not equal\n");
    } else {
        printf("FAIL: matrix_a and matrix_c are equal\n");
    }
}


int main() {
    test_matmul();
    test_transpose();
    test_softmax();
    test_scale();
    test_is_equal();
    return 0;
}
