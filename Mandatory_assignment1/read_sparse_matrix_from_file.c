#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

void read_sparse_matrix_from_file(const char *filename, struct sparse_mat_coo *matrix) {

    // File pointer
    FILE *file;

    // Opening file in read mode ("r")
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error in opening file");
        exit(EXIT_FAILURE);
    }

    int m_rows, n_cols, total_values;

    const int LINE_BUFFER = 256;
    char line_in_file[LINE_BUFFER];
    // Scan through file, break after collecting matrix info on the first line after the comments in file
    while (fgets(line_in_file, sizeof(line_in_file), file) != NULL) {
        
        if (line_in_file[0] == '%') {
            /* Pass */;
        }
        else {
            sscanf(line_in_file, "%d %d %d", &m_rows, &n_cols, &total_values);
            break;
        }
    }

    if (m_rows != n_cols) {
        printf("Sparse data matrix NOT square");
        exit(EXIT_FAILURE);
    }

    int *rows = malloc(total_values*sizeof(*rows));
    int *cols = malloc(total_values*sizeof(*cols));
    double *values = malloc(total_values*sizeof(*values));
    // fgets will continue on the next line in file from where it left off above, first data point
    // Index first row of values as 0
    int i = 0;
    while (fgets(line_in_file, sizeof(line_in_file), file) != NULL) {

        if (sscanf(line_in_file, "%d %d %lf", &rows[i], &cols[i], &values[i]) == 3) {
            printf("%s", line_in_file);
            i += 1;
        }
    }
    
    fclose(file);

    // Asigning matrix values to struct
    // We just pick n to be the number of rows in the data matrix
    matrix->n = m_rows;
    matrix->nnz = total_values;
    matrix->row_idx = rows;
    matrix->col_idx = cols;
    matrix->val = values;
    
    // free(rows);
    // free(cols);
    // free(values);
}
