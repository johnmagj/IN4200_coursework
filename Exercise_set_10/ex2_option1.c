#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int nargs, char **args) {

    int rank;
    int size;

    MPI_Status status;

    MPI_Init(&nargs, &args);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int n = 10;

    // Seed rand with current time
    srand(rank + time(NULL));

    int sum = 0;
    for (int i = 0; i < n; i++) {
        // Random integer between 0 and 9
        sum += rand() % 10;
    }

    if (rank == 0) {
        printf("Sum from master rank %d: %d\n", rank, sum);

        int total_sum = sum;
        for (int i = 1; i < size; i++) {
            MPI_Recv(&sum, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            int rank_of_sender = status.MPI_SOURCE;
            printf("Sum from rank %d: %d\n", rank_of_sender, sum);
            total_sum += sum;
        }

        printf("In total we have: %d\n", total_sum);
    }

    else {
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}