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

    int min_rows_per_rank = N/size; // integer division since both numerator and denominator are int
    int reminder = N % size;
    
    int *rows_per_rank = malloc(size*sizeof(*rows_per_rank));;

    // For MPI_Scatterv
    int *send_counts = malloc(size*sizeof(*send_counts));
    int *send_displacements = malloc(size*sizeof(*send_displacements));
    // For MPI_Gatherv
    int *recv_displacements = malloc(size*sizeof(*recv_displacements));

    int threshold = size - reminder;
    int row_offset = 0;
    int y_offset = 0;
    for (int i = 0; i < size; i++) {
        int number_of_rows = min_rows_per_rank + (i >= threshold);

        rows_per_rank[i] = number_of_rows;
        send_counts[i] = number_of_rows*N;
        send_displacements[i] = row_offset;
        row_offset += send_counts[i];

        recv_displacements[i] = y_offset;
        y_offset += number_of_rows;
    }

    # define idx(i, j) (i*N + j)
    double *A = NULL;
    double *x = malloc(N*sizeof(*x));

    if (rank == root_rank) {
        A = malloc(N*N*sizeof(*A));
        // Fill matrix A and vector x with ones
        for (int i = 0; i < N; i++) {
            x[i] = 1.0;
            for (int j = 0; j < N; j++) {
                A[idx(i, j)] = 1.0;
            }
        }
    }
    else {
        A = malloc(rows_per_rank[rank]*N*sizeof(*A));
    }

    double *A_recv = malloc(rows_per_rank[rank]*N*sizeof(*A_recv));

    MPI_Bcast(x, N, MPI_DOUBLE, root_rank, MPI_COMM_WORLD);
    MPI_Scatterv(A, send_counts, send_displacements, MPI_DOUBLE, A_recv, send_counts[rank], MPI_DOUBLE, root_rank, MPI_COMM_WORLD);

    double *y = NULL;
    double *y_recv = NULL;
    if (rank == root_rank) {
        y = malloc(N*sizeof(*y));
        y_recv = malloc(N*sizeof(*y_recv));
    }
    else {
        y = malloc(rows_per_rank[rank]*sizeof(*y));
        y_recv = malloc(rows_per_rank[rank]*sizeof(*y_recv));
    }

    // The actual matrix multiplication
    for (int i = 0; i < rows_per_rank[rank]; i++) {
        y[i] = 0;
        for (int j = 0; j < N; j++) {
            y[i] += A_recv[idx(i, j)]*x[j];
        }
    }

    MPI_Gatherv(y, rows_per_rank[rank], MPI_DOUBLE, y_recv, rows_per_rank, recv_displacements, MPI_DOUBLE, root_rank, MPI_COMM_WORLD);

    if (rank == root_rank) {

        for (int i = 0; i < N; i++) {
            printf("%d, %f\n", i, y_recv[i]);
        }
    }

    free(rows_per_rank);
    free(A);
    free(A_recv);
    free(x);
    free(y);
    free(y_recv);
    free(send_counts);
    free(send_displacements);
    free(recv_displacements);

    MPI_Finalize();

    return 0;
}

// Done