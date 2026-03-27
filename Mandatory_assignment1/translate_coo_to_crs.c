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

    int n = mat_coo->n;
    int nnz = mat_coo->nnz;
    int *row_indices = mat_coo->row_idx;
    int *cols_indices = mat_coo->col_idx;
    double *vals = mat_coo->val;

    // Since the the data in the matrix market format file can be both row or column sorted (or even unsorted),
    // we start by sorting the data by row index, then column index
    odd_even_sort_2_of_3_arrays(nnz, row_indices, cols_indices, vals);

    for (int i = 0; i < nnz; i++) {
        printf("i: %d, row: %d, col: %d, val: %f\n", i, row_indices[i], cols_indices[i], vals[i]);
    }

    // Now we can translate to CRS format
    // NOTE TO SELF: WE READ 1-based values, AND FILL USING 0-based INDEXING
    mat_crs->col_idx = cols_indices;
    mat_crs->val = vals;

    int ptr_id = 0;
    for (int i = 1; i < nnz; i++) {
        row_indices[i];

        ptr_id += 1;
    }

    int *intermediate_row_ptr = row_indices;
    intermediate_row_ptr[0] = 0;
    int current_row = row_indices[0];
    int id = 0;
    for (int index = 1; index < nnz; index++) {
        if (row_indices[index] == current_row) {
            intermediate_row_ptr[index] = 0;
        }

        else {
            id += 1;
            intermediate_row_ptr[index] = id;
            current_row += 1;
        }
    }

    for (int i = 0; i < 20; i++) {
        printf("%d\n", intermediate_row_ptr[i]);
    }

    // int counter = 0;
    // int counter_zeros = 0;
    // int id = 0;
    // for (int i = 0; i < nnz; i++) {
    //     if (intermediate_row_ptr[i] != 0) {
    //         mat_crs->row_ptr[id] = i;
    //         id += 1;
    //     }
    // }

    // for (int i = 0; i < n+1; i++) {
    //     printf("%d\n", mat_crs->row_ptr[i]);
    // }

}