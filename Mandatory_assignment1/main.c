#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

int main(int nargs, char **args) {

    char filename_path[256];
    //char filename_path[] = "Data/1138_bus.mtx";
    double **A, **B;
    struct sparse_mat_coo S_coo, C_coo;
    //struct spare_mat_crs S_crs, C_crs;
    
    printf("Enter relative file path to the .mtx file:");
    scanf("%s", &filename_path);
    
    // printf("%s", filename_path);

    read_sparse_matrix_from_file(filename_path, &S_coo);

    printf("--------------------------------\n");
    printf("For file: %s\n", filename_path);
    printf("n: %d, nnz: %d\n", S_coo.n, S_coo.nnz);
    printf("First: %d, %d, %f\n", S_coo.row_idx[0], S_coo.col_idx[0], S_coo.val[0]);
    printf("Last: %d, %d, %f\n", S_coo.row_idx[S_coo.nnz-1], S_coo.col_idx[S_coo.nnz-1], S_coo.val[S_coo.nnz-1]);
    printf("--------------------------------");

    free(S_coo.row_idx);
    free(S_coo.col_idx);
    free(S_coo.val);

    return 0;
}