#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

void sampled_matrix_multiplication_coo(struct sparse_mat_coo *C, double **A, double **B, struct sparse_mat_coo *S) {

    int n = S->n;
    int nnz = S->nnz;
   
    for (int index = 0; index < nnz; index++) {
        // The row and column indicies stored in the .mtx file is based on a 1-based matrix,
        // we therefore subtract 1 to make them compatible with our 0-based arrays
        int i = S->row_idx[index] - 1;
        int j = S->col_idx[index] - 1;

        double sum = 0;
        for (int k = 0; k < n; k++) {
            sum += A[i][k]*B[k][j];
        } 

        C->val[index] = sum*S->val[index];
    }

}