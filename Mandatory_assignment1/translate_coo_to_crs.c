#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

void translate_coo_to_crs (struct sparse_mat_coo *mat_coo, struct sparse_mat_crs *mat_crs) {

    int n = mat_coo->n;
    int nnz = mat_coo->nnz;

    

    // Since the the data in the matrix market format file can be both row or column sorted (or even unsorted),
    // we start by sorting the data by row index, then column index
    for (int i = 0; i < nnz; i++) {

        mat_coo->row_idx[index]
    }



    for (int index = 0; index < nnz; index++) {
        
        mat_crs->val[index] = mat_coo->val[index];

        mat_crs->col_idx[index] = mat_coo->col_idx[index];
        
        mat_coo->row_idx[index]
    }
    
}
