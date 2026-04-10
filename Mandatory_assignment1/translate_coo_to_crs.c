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

        if (counter % 1000 == 0) {
            printf("    Sort counter (per 1000 iteration): %d, number of swaps this iteration: %d \n", counter, total_number_of_swaps);
        }

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
    printf("    Sort STARTED\n");
    odd_even_sort_2_of_3_arrays(nnz, row_indices, cols_indices, vals);
    printf("    Sort DONE\n");

    // Copy over the sorted arrays cols_indices and vals so that row_indices, cols_indices and vals can be freed later
    memcpy(mat_crs->col_idx, cols_indices, nnz * sizeof(int));
    memcpy(mat_crs->val, vals, nnz * sizeof(double));

    mat_crs->row_ptr[0] = 0;
    int current_row = 0;

    // Realize that the indices of the row_ptr array represent the rows of the full sparse matrix.
    // Since we assuming sparse matrices some of the rows might be empty as thus not appearing in row_indices.
    // We therfore need a logic that can handle a row_indices array like [2,2,4,5] (for a 7x7 sparse matrix).
    // Here row 0,1,3, and 6 are missing, indicating they contain only zeros.
    // We have a new row appearing on index 0, 2, and 3.
    // To indicate the end of the row_ptr array the last element (index: n+1-1) would be the first out of bounds index of row_indices (nnz+1-1), 
    // so in this case 4, this to comply with the CRS format.
    // Missing rows and repeated rows between each new row should in row_ptr have the same element value (index of row_indices)
    // as the index of the expected upcoming new row.
    // The correct row_ptr should in this case be: [0,0,0,2,2,3,4,4].

    for (int i = 0; i < nnz; i++) {

        while (row_indices[i] > current_row) {
            current_row += 1;
            mat_crs->row_ptr[current_row] = i;
        }
    }

    // Since empty rows at the end of the sparse matrix is not counted for in the loop above, 
    // we must continue from (current_row + 1) iterating to the end of row_ptr (with len n+1, typically >> nnz).
    // If last element is nonzero then we fill the last element (n+1) with "out of bounds index" for val array (nnz).
    
    for (int i = current_row + 1; i < n+1; i++) {
        mat_crs->row_ptr[i] = nnz;
    }
        
    // for (int i = 0; i < n+1; i++) {
    //     printf("%d\n", mat_crs->row_ptr[i]);
    // }

    // We can free the memory of the sorted arrays
    free(row_indices);
    free(cols_indices);
    free(vals);
}