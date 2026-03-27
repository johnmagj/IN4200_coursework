#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

int main(int nargs, char **args) {

    char filename_path[256];
    //char filename_path[] = "Data/1138_bus.mtx";
    double **A, **B;
    struct sparse_mat_coo S_coo, C_coo;
    struct sparse_mat_crs S_crs, C_crs;
    
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
    A = malloc(n * sizeof(*A));
    A[0] = malloc(n*n*sizeof(*A[0]));

    B = malloc(n * sizeof(*B));
    B[0] = malloc(n*n*sizeof(*B[0]));

    for (int i = 1; i < n; i++) {
        A[i] = &(A[0][i*n]);
        B[i] = &(B[0][i*n]);
    }
    // Fill A and B with some values
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }

    sampled_matrix_multiplication_coo(&C_coo, A, B, &S_coo);

    // allocate CRS data structure C_crs
    S_crs.n = S_coo.n; S_crs.nnz = S_coo.nnz;
    S_crs.row_ptr = (int*)malloc((S_crs.n+1) * sizeof(int));
    S_crs.col_idx = (int*)malloc(S_crs.nnz * sizeof(int));
    S_crs.val = (double*)malloc(S_crs.nnz * sizeof(double));


    translate_coo_to_crs(&S_coo, &S_crs);


    free(S_coo.row_idx);
    free(S_coo.col_idx);
    free(S_coo.val);
    free(C_coo.val);
    free(A[0]);
    free(A);
    free(B[0]);
    free(B);

    return 0;
}
