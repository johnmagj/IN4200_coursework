#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int nargs, char **args) {

    int rank;
    int size;

    MPI_Init(&nargs, &args);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int root_rank = 0;

    int N = 10;

    int *y = malloc(N*sizeof(*y)); 

    if (rank = root_rank) {

        # define idx(i, j) (i*N + j)
        
        int *A = malloc(N*N*sizeof(*A));
        int *x = malloc(N*sizeof(*A));

        for (int i = 0; i < N; i++) {
            x[i] = 1;
            for (int j = 0; j < N, j++) {
                A[idx(i, j)] = 1;
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N, j++) {

                Send(A[idx(i, j)], )
                Send(x[i], )
            }
        }

        free(A);
        free(x);
    }

    else {
        Receive(A[idx(i, j)])
        Receive(x[i])

        int row_sum = 0; 
        for (int elem = 0; elem < N; elem++) {
            row_sum += A[idx(elem, j)]*x[elem]
        }

        y[elem] = row_sum

        Send(y)
    }

    free(y);

    MPI_Finalize();

    return 0;
}