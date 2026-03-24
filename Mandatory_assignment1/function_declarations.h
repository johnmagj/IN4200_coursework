#ifndef FUNCTION_DECLARATIONS_H
#define FUNCTION_DECLARATIONS_H

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

#endif