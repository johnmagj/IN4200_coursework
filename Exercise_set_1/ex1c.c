#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    int m = 10000;
    int n = 10000;

    int **arr1 = malloc(m*sizeof(*arr1));
    int **arr2 = malloc(m*sizeof(*arr2));

    for (int i = 0; i < m; i++) {
        arr1[i] = malloc(n * sizeof(*arr1));
        arr2[i] = malloc(n * sizeof(*arr2));
    }

    clock_t t_start, t_stop;
    double t_tot;

    t_start = clock();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {

            arr1[i][j] = 1;

            // printf("%p ", &matrix_1[i][j]);
        }
        // printf("\n");
    }
    t_stop = clock();
    t_tot = (double)(t_stop - t_start)/CLOCKS_PER_SEC;
    printf("%f\n", t_tot);

    t_start = clock();
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {

            arr2[i][j] = 1;

            // printf("%p ", &matrix_2[i][j]);
        }
        // printf("\n");
    }
    t_stop = clock();
    t_tot = (double)(t_stop - t_start)/CLOCKS_PER_SEC;
    printf("%f\n", t_tot);

    printf("%d\n", arr1[0][0]);
    printf("%d\n", arr2[0][0]);

    for (int i = 0; i < m; i++) {
        free(arr1[i]);
        free(arr2[i]);
    }

    free(arr1);
    free(arr2);

    return 0;
}

// Done