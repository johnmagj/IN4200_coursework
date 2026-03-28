#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

void sampled_matrix_multiplication_crs(struct sparse_mat_crs *C, double **A, double **B, struct sparse_mat_crs *S) {

    int n = S->n;
    int nnz = S->nnz;
   
    for (int i = 0; i < n+1; i++) {

    }

}