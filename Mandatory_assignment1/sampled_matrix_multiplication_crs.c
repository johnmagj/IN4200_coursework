#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

void sampled_matrix_multiplication_crs(struct sparse_mat_crs *C, double **A, double **B, struct sparse_mat_crs *S) {

    int n = S->n;
    int nnz = S->nnz;
   
    int current_row = 1;
    int current_val_index = -1;
    
    for (int index = 0; index < n+1; index++) {

        if (S->row_ptr[index] > current_val_index) {
        
            int i = current_row - 1;
            int j = S->col_idx[index] - 1;

            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += A[i][k]*B[k][j];
            }

            C->val[index] = sum*S->val[index];

            current_row += 1;
            current_val_index += 1;
        }

        else {

        }
    }

}