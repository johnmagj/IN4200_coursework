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

    int n = 10;

    // Seed rand with current time
    srand(rank + time(NULL));

    int sum = 0;
    for (int i = 0; i < n; i++) {
        // Random integer between 0 and 9
        sum += rand() % 10;
    }

    int total_sum = 0;

    MPI_Reduce(&sum, &total_sum, 1, MPI_INT, MPI_SUM, root_rank, MPI_COMM_WORLD);

    if (rank == root_rank) {
        printf("Total sum: %d\n", total_sum);
    }

    MPI_Finalize();

    return 0;
}