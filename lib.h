#ifndef LIB_H
#define LIB_H

void print_matrix(int n, int m, float (*matrix)[n]);
void init_matrix(int n, int m, float (*matrix)[n]);
void matmul(int n, int m, int x, float (*matrix_a)[m], float (*matrix_b)[x], float (*result)[x]);
void transpose(int n, int m, float (*matrix)[m], float (*result)[n]);
void softmax(int n, int m, float (*matrix)[m], float (*result)[m]);

#endif /* LIB_H */
