#ifndef LIB_H
#define LIB_H

void print_matrix(int n, int m, float (*matrix)[n]);
void init_matrix(int n, int m, float (*matrix)[n]);
void matmul(int n, int m, float (*matrix_a)[n], float (*matrix_b)[m], float (*result)[n]);

#endif /* LIB_H */
