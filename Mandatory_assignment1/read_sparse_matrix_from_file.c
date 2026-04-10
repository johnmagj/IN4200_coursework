#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

void read_sparse_matrix_from_file(const char *filename, struct sparse_mat_coo *matrix) {

    // File pointer
    FILE *file;

    // Opening file in read mode ("r")
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error: could not open file correctly ");
        exit(EXIT_FAILURE);
    }

    int m_rows = 0;
    int n_cols = 0;
    int total_values = 0;

    const int LINE_BUFFER = 256;
    char line_in_file[LINE_BUFFER];

    // Check first line in file, if not starting with a '%', exit program
    fgets(line_in_file, sizeof(line_in_file), file);
    if (line_in_file[0] != '%') {
        printf("Error: file not formatted correctly ");
        exit(EXIT_FAILURE);
    }

    // Scan through file, break after collecting matrix info on the first line after the comments in file
    // If exit program if the line containing matrix information is not format correctly
    while (fgets(line_in_file, sizeof(line_in_file), file) != NULL) {
        
        if (line_in_file[0] == '%') {
            /* Pass */;
        }
        else {

            if (sscanf(line_in_file, "%d %d %d", &m_rows, &n_cols, &total_values) != 3) {
                printf("Error: first line with matrix-information not formatted correctly ");
                exit(EXIT_FAILURE);
            }

            else {
                sscanf(line_in_file, "%d %d %d", &m_rows, &n_cols, &total_values);
                break;
            }
        }
    }

    if (m_rows == 0 || n_cols == 0 || total_values == 0) {
        printf("Error: matrix info was not stored properly, should be non zero ");
        exit(EXIT_FAILURE);
    }

    if (m_rows != n_cols) {
        printf("Error: the sparse data matrix is NOT square ");
        exit(EXIT_FAILURE);
    }

    int *rows = malloc(total_values*sizeof(*rows));
    int *cols = malloc(total_values*sizeof(*cols));
    double *values = malloc(total_values*sizeof(*values));
    // fgets will continue on the next line in file from where it left off above, first data point
    // Index first row of values as 0
    int i = 0;
    while (fgets(line_in_file, sizeof(line_in_file), file) != NULL) {
        double temp_row;
        double temp_col;

        // We read floats in line_in_file since a line like: 5 1.4989, would be read 5, 1, 0.4989 with %d %d %lf,
        // this would again not trigger the check line check right bellow.
        // Explicitly casting back to int with (int) 
        if (sscanf(line_in_file, "%lf %lf %lf", &temp_row, &temp_col, &values[i]) == 3) {
            rows[i] = (int)temp_row;
            cols[i] = (int)temp_col;
            i += 1;
        }

        else {
            printf("Data line not formatted correctly, data line: %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    
    fclose(file);

    // Assigning matrix values to struct
    // We just pick n to be the number of rows in the data matrix
    matrix->n = m_rows;
    matrix->nnz = total_values;
    matrix->row_idx = rows;
    matrix->col_idx = cols;
    matrix->val = values;
    
}