#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "function_declarations.h"

void sampled_matrix_multiplication_coo(struct sparse_mat_coo *C, double **A, double **B, struct sparse_mat_coo *S) {

    int n = S->n;
    int nnz = S->nnz;

    #pragma omp parallel for
    for (int index = 0; index < nnz; index++) {

        int i = S->row_idx[index];
        int j = S->col_idx[index];

        double sum = 0;
        for (int k = 0; k < n; k++) {
            sum += A[i][k]*B[k][j];
        } 

        C->val[index] = sum*S->val[index];
    }
    
}