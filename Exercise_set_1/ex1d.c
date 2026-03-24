#include <stdio.h>
#include <stdlib.h>

int main() {

    int rows = 5;
    int cols = 5;
    int layers = 3;

    int *arr = malloc(rows*cols*layers*sizeof(*arr));

    // The first layer i.e. l=0, occupies the first rows*cols elements

    #define idx(l, r, c) (l*rows*cols + r*cols + c)

    for (int l = 0; l < layers; l++) {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                arr[idx(l, r, c)] = idx(l, r, c);
                printf("%d ", arr[idx(l, r, c)]);
            }
            printf("\n");
        }
        printf("\n");
    }

    free(arr);

    return 0;
}