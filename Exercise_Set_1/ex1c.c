#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    int m = 3;
    int n = 3;

    clock_t t_start, t_stop;
    double t_tot;
    t_start = clock();

    int matrix_1[m][n];

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {

            matrix_1[i][j] = 1;

            printf("%p ", &matrix_1[i][j]);
        }
        printf("\n");
    }

    t_stop = clock();
    t_tot = (double)(t_stop - t_start);

    printf("%f\n", t_tot);

    t_start = clock();

    int matrix_2[m][n];

    for(int j = 0; j < m; j++) {
        for(int i = 0; i < n; i++) {

            matrix_2[i][j] = 1;

            printf("%p ", &matrix_2[i][j]);
        }
        printf("\n");
    }

    t_stop = clock();
    t_tot = (double)(t_stop - t_start);
    
    printf("%f", t_tot);

    return 0;
}