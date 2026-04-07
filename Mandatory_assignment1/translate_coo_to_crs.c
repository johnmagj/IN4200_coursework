#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function_declarations.h"

void swap_ints(int *elem_A, int *elem_B) {
    int new_A = *elem_B;
    int new_B = *elem_A;
    *elem_A = new_A;
    *elem_B = new_B;
}

void swap_doubles(double *elem_A, double *elem_B) {
    double new_A = *elem_B;
    double new_B = *elem_A;
    *elem_A = new_A;
    *elem_B = new_B;
}

void odd_even_sort_2_of_3_arrays(int n, int *arr1, int *arr2, double *arr3) {
    // Sort arrays of matrix, first by arr1, then by arr2

    int total_number_of_swaps;
    int counter = 0;

    do {
        total_number_of_swaps = 0;
        int number_of_swaps_row_based = 0;
        int number_of_swaps_column_based = 0;

        // For the odd indices
        for (int j = 1; j < n - 1; j+=2) {
            if (arr1[j] > arr1[j+1]) {   
                swap_ints(&arr1[j], &arr1[j+1]);
                swap_ints(&arr2[j], &arr2[j+1]);
                swap_doubles(&arr3[j], &arr3[j+1]);
                number_of_swaps_row_based += 1;
            }

            if (arr1[j] == arr1[j+1]) {
                // Check arr2
                if (arr2[j] > arr2[j+1]) {
                    swap_ints(&arr1[j], &arr1[j+1]);
                    swap_ints(&arr2[j], &arr2[j+1]);
                    swap_doubles(&arr3[j], &arr3[j+1]);
                    number_of_swaps_column_based += 1;
                }
            }
        }
        // For the even indices
        for (int j = 0; j < n - 1; j+=2) {
            if (arr1[j] > arr1[j+1]) {
                swap_ints(&arr1[j], &arr1[j+1]);
                swap_ints(&arr2[j], &arr2[j+1]);
                swap_doubles(&arr3[j], &arr3[j+1]);
                number_of_swaps_row_based += 1; 
            }

            if (arr1[j] == arr1[j+1]) {
                // Check arr2
                if (arr2[j] > arr2[j+1]) {
                    swap_ints(&arr1[j], &arr1[j+1]);
                    swap_ints(&arr2[j], &arr2[j+1]);
                    swap_doubles(&arr3[j], &arr3[j+1]);
                    number_of_swaps_column_based += 1;
                }
            }
        }
        total_number_of_swaps = number_of_swaps_row_based + number_of_swaps_column_based;
        // printf("Total number of swaps: %d\n", total_number_of_swaps);
        // printf("Row swaps: %d\n", number_of_swaps_row_based);
        // printf("Col swaps: %d\n", number_of_swaps_column_based);
        counter += 1;
    } while (total_number_of_swaps > 0);
}

void translate_coo_to_crs (struct sparse_mat_coo *mat_coo, struct sparse_mat_crs *mat_crs) {

    int n = mat_coo->n;
    int nnz = mat_coo->nnz;

    // Create copies of the arrays in struct spare_mat_coo *mat_coo to be used in the preceding calculation,
    // in case the original is needed later in the main program
    int *row_indices = malloc(nnz*sizeof(*row_indices));
    int *cols_indices = malloc(nnz*sizeof(*cols_indices));
    double *vals = malloc(nnz*sizeof(*vals));
    memcpy(row_indices, mat_coo->row_idx, nnz*sizeof(*row_indices));
    memcpy(cols_indices, mat_coo->col_idx , nnz*sizeof(*cols_indices));
    memcpy(vals, mat_coo->val, nnz*sizeof(*vals));

    // Since the the data in the matrix market format file can be both row or column sorted, or even unsorted,
    // we sort the data by row index, then column index
    odd_even_sort_2_of_3_arrays(nnz, row_indices, cols_indices, vals);

    // Copy over the sorted arrays cols_indices and vals
    memcpy(mat_crs->col_idx, cols_indices, nnz * sizeof(int));
    memcpy(mat_crs->val, vals, nnz * sizeof(double));

    mat_crs->row_ptr[0] = 0;
    int current_row = 0;

    for (int i = 0; i < nnz; i++) {

        while (row_indices[i] > current_row) {
            current_row += 1;
            mat_crs->row_ptr[current_row] = i;
        }
    }

    for (int i = current_row + 1; i < n+1; i++) {
        mat_crs->row_ptr[i] = nnz;
    }
        
    printf("loop done\n"); 

    printf("current row: %d\n", current_row);

    for (int i = 0; i < n+1; i++) {
        printf("%d\n", mat_crs->row_ptr[i]);
    }

    // We can free the memory of the sorted arrays
    free(row_indices);
    free(cols_indices);
    free(vals);

}