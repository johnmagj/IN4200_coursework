#include <stdio.h>
#include <stdlib.h>
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
    int *row_indices = mat_coo->row_idx;
    int *cols_indices = mat_coo->col_idx;
    double *vals = mat_coo->val;

    // Since the the data in the matrix market format file can be both row or column sorted (or even unsorted),
    // we sort the data by row index, then column index
    odd_even_sort_2_of_3_arrays(nnz, row_indices, cols_indices, vals);

    // for (int i = 0; i < nnz; i++) {
    //     printf("i: %d, row: %d, col: %d, val: %f\n", i, row_indices[i], cols_indices[i], vals[i]);
    // }

    // Convert arrays to 0 based indexing
    for (int i = 0; i < nnz; i++){
        row_indices[i] -= - 1;
        cols_indices[i] -= -1;
    }

    mat_crs->col_idx = cols_indices;
    mat_crs->val = vals;

    // Set all elements of the CRS row ptr to zero
    for (int i = 0; i < n+1; i++) {
        mat_crs->row_ptr[i] = 0;
    }

    // The row indices are base 1, check if there are empty leading rows
    if (row_indices[0] != 0) {
        for (int i = 0; i < row_indices[0]; i++) { 
            mat_crs->row_ptr[i] = 0;
        }
    }

    // Create new array identical to row_indices so we won't overwrite it next
    int *intermediate_row_ptr = malloc(nnz*sizeof(*intermediate_row_ptr));
    for (int i = 0; i < nnz; i++) {
        intermediate_row_ptr[i] = row_indices[i]; 
    }
    // Trailing rows of same number are set to zero
    intermediate_row_ptr[0] = row_indices[0];
    for (int i = 0; i < nnz; i++) {
        if (intermediate_row_ptr[i] == row_indices[i-1]) {
            intermediate_row_ptr[i] = 0;
        }
    }
    // 
    int ptr_id = 0;
    int ptr_idx = 0;
    for (int i = 0; i < nnz; i++) {
        if (intermediate_row_ptr[i] != 0) {
            mat_crs->row_ptr[ptr_idx] = ptr_id;
            ptr_idx += 1;
        }
    
        if (intermediate_row_ptr[i] == 0) {
            mat_crs->row_ptr[ptr_idx] = ptr_id;
        }
        ptr_id += 1;
    }

    // for (int i = 0; i <= n; i++) {
    //     printf("row_ptr: %d, inter_ptr: %d\n", mat_crs->row_ptr[i], intermediate_row_ptr[i]);
    // }

    free(intermediate_row_ptr);

}