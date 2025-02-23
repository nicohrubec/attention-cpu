#ifndef LIB_H
#define LIB_H

void print_matrix(int n, int m, float (*matrix)[n]);
void init_matrix(int n, int m, float (*matrix)[n]);
void matmul(int n, int m, int x, float (*matrix_a)[m], float (*matrix_b)[x], float (*result)[x]);
void fast_matmul(int n, int m, int x, float (*matrix_a)[m], float (*matrix_b)[x], float (*result)[x]);
void transpose(int n, int m, float (*matrix)[m], float (*result)[n]);
void fast_transpose(int n, int m, float (*matrix)[m], float (*result)[n]);
void softmax(int n, int m, float (*matrix)[m]);
void fast_softmax(int n, int m, float (*matrix)[m]);
void scale(int n, int m, float (*matrix)[m], float scalar);
void fast_scale(int n, int m, float (*matrix)[m], float scalar);
int is_equal(int n, int m, float (*matrix_a)[m], float (*matrix_b)[m]);

#endif /* LIB_H */
