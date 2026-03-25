#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

int main(int nargs, char **args) {

    char filename_path[256];
    //char filename_path[] = "Data/1138_bus.mtx";

    struct sparse_mat_coo S_coo, C_coo;
    //struct spare_mat_crs S_crs, C_crs;
    
    printf("Enter relative file path to the .mtx file:");
    scanf("%s", filename_path);
    
    // printf("%s", filename_path);

    read_sparse_matrix_from_file(filename_path, &S_coo);

    printf("--------------------------------\n");
    printf("For file: %s\n", filename_path);
    printf("n: %d, nnz: %d\n", S_coo.n, S_coo.nnz);
    printf("First: %d, %d, %f\n", S_coo.row_idx[0], S_coo.col_idx[0], S_coo.val[0]);
    printf("Last: %d, %d, %f\n", S_coo.row_idx[S_coo.nnz-1], S_coo.col_idx[S_coo.nnz-1], S_coo.val[S_coo.nnz-1]);
    printf("--------------------------------\n");

    C_coo.n = S_coo.n; 
    C_coo.nnz = S_coo.nnz;
    C_coo.row_idx = S_coo.row_idx;
    C_coo.col_idx = S_coo.col_idx;
    C_coo.val = malloc(C_coo.nnz*sizeof(*C_coo.val));
    
    int n = S_coo.n;
    // Create dense matrices A and B, 
    double *A = malloc(n*n*sizeof(*A));
    double *B = malloc(n*n*sizeof(*B));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[idx(i,j)] = i + j;
            B[idx(i,j)] = 2*i + 3*j;
            if (i < 5 && j < 5) {
                printf("%g ", B[idx(i,j)]);
            }
        if (i < 5) {
            printf("\n");
        }
    }
    
    printf("%f", B[idx(10,10)]);

    sampled_matrix_multiplication_coo(&C_coo, A, B, &S_coo);

    free(S_coo.row_idx);
    free(S_coo.col_idx);
    free(S_coo.val);
    free(A);
    free(B);

    return 0;
}