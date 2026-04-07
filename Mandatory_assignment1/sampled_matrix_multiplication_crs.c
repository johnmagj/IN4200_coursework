#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

void sampled_matrix_multiplication_crs(struct sparse_mat_crs *C, double **A, double **B, struct sparse_mat_crs *S) {

    int n = S->n;
    int nnz = S->nnz;
   
    // The indices of S->row_ptr are the rows of the sparse matrix
    for (int i = 0; i < n; i++) {

        if (S->row_ptr[i] < S->row_ptr[i+1]) {
            
            // The columns and values arrays in CRS have the same indexing
            for (int col_val_index = S->row_ptr[i]; col_val_index < S->row_ptr[i+1]; col_val_index++) {

                int j = S->col_idx[col_val_index];

                double sum = 0;
                for (int k = 0; k < n; k++) {
                    sum += A[i][k]*B[k][j];
                }
                // printf("(%d, %d) %f\n", i+1, j+1, S->val[col_val_index]);
                C->val[col_val_index] = sum*S->val[col_val_index];
            }
        }
    }

}