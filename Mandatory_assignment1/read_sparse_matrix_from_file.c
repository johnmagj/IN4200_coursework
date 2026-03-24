#include <stdio.h>

void read_sparse_matrix_from_file(const char *filename, struct sparse_mat_coo *matrix) {

    // File pointer
    FILE *file;

    // Opening file in read mode ("r")
    file = fopen("Data/psmigr_1.mtx", "r");

    if (file == NULL) {
        printf("Error in opening file");
        return 1;
    }

    const int LINE_BUFFER = 256;
    char line_in_file[LINE_BUFFER];

    int m, n, total_values;

    // 
    while (fgets(line_in_file, sizeof(line_in_file), file) != NULL) {
        
        if (line_in_file[0] == '%') {
            /* Pass */;
        }
        else {
            // printf("%s", line_buffer);
            sscanf(line_in_file, "%d %d %d", &m, &n, &total_values);
            break;
        }
    }

    int *rows = malloc(total_values*sizeof(*rows));
    int *cols = malloc(total_values*sizeof(*cols));
    double *values = malloc(total_values*sizeof(*values));

    // fgets will continue on the next line in file from where it left off above 
    // Index first row of values as 0
    int i = 0;
    while (fgets(line_in_file, sizeof(line_in_file), file) != NULL) {

        if (i%100000 == 0) {
            printf("%s", line_in_file);
        }

        sscanf(line_in_file, "%d %d %lf", &rows[i], &cols[i], &values[i]);
        i += 1;
    }
    
    fclose(file);

    printf("i = %d\n", i);

    printf("num header lines: %d\n", num_header_lines);
    printf("m: %d, n: %d, tot values: %d\n", m, n, total_values);

    printf("%d, %d, %f\n", rows[0], cols[0], values[0]);
    printf("%d, %d, %f\n", rows[total_values-1], cols[total_values-1], values[total_values-1]);

    free(rows);
    free(cols);
    free(values);

}

