#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

void sampled_matrix_multiplication_coo(struct sparse_mat_coo *C, double *A, double *B, struct sparse_mat_coo *S) {

    int nnz = S->nnz;

   
    for (int index = 0; index < nnz; index++) {

        int i = S->row_idx[index];
        int j = S->col_idx[index];

        for (int k = 0; k < nnz; k++) {
            

        } 


        for (int j = 0; j < nnz; j++) {

            int sum = 0;
            for (int k = 0; k < nnz; k++) {
                sum += A[idx(i,k)]*B[idx(k,j)];
            }


            
            S_i = S->row_idx[i];
            S_j = S->col_idx[j];



            Ci = C->row_idx[i];

            C->row_idx = ;
            C->col_idx = ;
            C->val = ;
            printf("%f", a);
        }
    }

}