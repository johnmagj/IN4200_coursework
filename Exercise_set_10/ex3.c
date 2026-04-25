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

    int *sendcounts = NULL;
    int *displacements = NULL;

    // Logic for deciding how many rows each process gets
    if (N < size) {
        sendcounts = calloc(size, sizeof(*sendcounts));
        sendcounts[0] = {N};

        displacements = calloc(size, sizeof(*sendcounts));
    } 
    else if (N % size == 0) {
        sendcounts = malloc(size*sizeof(*sendcounts));
        int rows_per_rank = N/size;
        for (int i = 0; i < size; i++) {
            sendcounts[i] = rows_per_rank;
        }
        displacements = malloc(size*sizeof(*sendcounts));
        for (int i = 0; i < size; i++) {
            displacements[i] = i*rows_per_rank;
        }
    }
    else if (N % size != 0) {
        sendcounts = malloc(size*sizeof(*sendcounts));
        int rows_per_rank = (N - (N % size))/size;
        for (int i = 0; i < size-1; i++) {
            sendcounts[i] = rows_per_rank;
        }
        sendcounts[size-1] = rows_per_rank + 
    }

    double *A_row_recv = malloc(N*sizeof(*A_row_recv));

    // So we can use MPI_Bcast later
    double *x = NULL;
    double *y = NULL; 

    if (rank == root_rank) {

        # define idx(i, j) (i*N + j)
        
        double *A = malloc(N*N*sizeof(*A));
        x = malloc(N*sizeof(*A));

        // Fill matrix A and vector x with ones
        for (int i = 0; i < N; i++) {
            x[i] = 1.0;
            for (int j = 0; j < N, j++) {
                A[idx(i, j)] = 1.0;
            }
        }

    MPI_Scatter(&A[idx(row_idx, 0)], N, MPI_DOUBLE, &A_row_recv, MPI_DOUBLE, root_rank, MPI_COMM_WORLD);
    MPI_Bcast(x, 1, MPI_DOUBLE, root_rank, MPI_COMM_WORLD);
    
    free(A);
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

    free(x);
    free(y);

    MPI_Finalize();

    return 0;
}