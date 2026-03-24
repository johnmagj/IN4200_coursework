#include <stdio.h>

void read_sparse_matrix_from_file(char *filename, struct sparse_mat_coo *matrix) {

    // File pointer
    FILE * file;

    // Opening file in read mode ("r")
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error in opening file");
        return;
    }

    int N;
    fscanf(file, "%d", &N);
    printf("N = %d\n", N);

    fclose(file);

}

