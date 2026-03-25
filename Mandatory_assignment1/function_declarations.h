#ifndef FUNCTION_DECLARATIONS_H
#define FUNCTION_DECLARATIONS_H

#define idx(i,j) (i*n + j)

struct sparse_mat_coo {
    int n, nnz;
    double *val;
    int *row_idx, *col_idx;
};

struct sparse_mat_crs {
    int n, nnz;
    double *val;
    int *row_idx, *col_idx;
};

void read_sparse_matrix_from_file(const char *filename, struct sparse_mat_coo *matrix);
void sampled_matrix_multiplication_coo(struct sparse_mat_coo *C, double *A, double *B, struct sparse_mat_coo *S);

#endif