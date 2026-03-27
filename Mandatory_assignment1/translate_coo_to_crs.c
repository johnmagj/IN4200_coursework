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

        for (int i = 0; i < (n+1)/2; i++) {
            // For the odd indices
            for (int j = 1; j < n - 1; j+=2) {
                if (arr1[j] > arr1[j+1]) {   
                    swap_ints(&arr1[j], &arr1[j+1]);
                    swap_ints(&arr2[j], &arr2[j+1]);
                    swap_doubles(&arr3[j], &arr3[j+1]);
                    number_of_swaps_row_based += 1;
                }

                if (arr1[j] == arr1[j+1]) {
                    if (arr2[j] > arr2[j+1]) {
                        swap_ints(&arr1[j], &arr1[j+1]);
                        swap_ints(&arr2[j], &arr2[j+1]);
                        swap_doubles(&arr3[j], &arr3[j+1]);
                        number_of_swaps_column_based += 1;
                    }
                }
            }
            
            // If even index
            for (int j = 0; j < n - 1; j+=2) {
                if (arr1[j] > arr1[j+1]) {
                    swap_ints(&arr1[j], &arr1[j+1]);
                    swap_ints(&arr2[j], &arr2[j+1]);
                    swap_doubles(&arr3[j], &arr3[j+1]);
                    number_of_swaps_row_based += 1; 
                }

                if (arr1[j] == arr1[j+1]) {
                    if (arr2[j] > arr2[j+1]) {
                        swap_ints(&arr1[j], &arr1[j+1]);
                        swap_ints(&arr2[j], &arr2[j+1]);
                        swap_doubles(&arr3[j], &arr3[j+1]);
                        number_of_swaps_column_based += 1;
                    }
                }
            }
        }
        total_number_of_swaps = number_of_swaps_row_based + number_of_swaps_column_based;
        printf("Total number of swaps: %d\n", total_number_of_swaps);
        printf("Row swaps: %d\n", number_of_swaps_row_based);
        printf("Col swaps: %d\n", number_of_swaps_column_based);
        counter += 1;
    } while (total_number_of_swaps > 0);

    printf("Counter: %d\n", counter);
}

void translate_coo_to_crs (struct sparse_mat_coo *mat_coo, struct sparse_mat_crs *mat_crs) {

    int nnz = mat_coo->nnz;
    int *row_indices = mat_coo->row_idx;
    int *cols_indices = mat_coo->col_idx;
    double *vals = mat_coo->val;

    // Since the the data in the matrix market format file can be both row or column sorted (or even unsorted),
    // we start by sorting the data by row index, then column index
    odd_even_sort_2_of_3_arrays(nnz, row_indices, cols_indices, vals);

    // for (int i = 0; i < nnz; i++) {
    //     printf("i: %d, row: %d, col: %d, val: %f\n", i, rows[i], cols[i], vals[i]);
    // }

    // Now we can translate to CRS format
    // REMEMBER: WE READ 1-based values, AND FILL USING 0-based INDEXING

    int prev_row = 0;
    for (int i = 0; i < nnz; i++) {

        if (row_indices[i] > prev_row) {
            // Indicate new row
            if (row_indices[i] > prev_row + 1) {
                // Indicate one or more sparse rows
                for (int r = 0; r < row_indices[i] - row_indices[i-1]; r++) {
                }
                
                row_indices[i-1];
            }

            else {
                mat_crs->col_idx[i] = cols_indices[i];
                mat_crs->val[i] = vals[i];
                mat_crs->row_ptr[i] = i + 1;

                prev_row += 1;
            }

        elif (row_indices[i] == prev_row) {
            // New value current row, different column
            mat_crs->col_idx[i] = cols_indices[i];
            mat_crs->val[i] = vals[i];
        }
    }

}