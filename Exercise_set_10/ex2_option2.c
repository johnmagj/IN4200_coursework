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

    int n = 10;

    // Seed rand with current time
    srand(rank + time(NULL));

    int sum = 0;
    for (int i = 0; i < n; i++) {
        // Random integer between 0 and 9
        sum += rand() % 10;
    }

    if (rank == 0) {
        int *receive_buffer = malloc(size*sizeof(*receive_buffer));
        int total_sum = 0;

        MPI_Gather(&sum , 1, MPI_INT, receive_buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

        for (int i = 0; i < size; i++) {
            printf("Stored sum, i=%d: %d\n", i, receive_buffer[i]);
            total_sum += receive_buffer[i];
        }

        printf("Total sum: %d\n", total_sum);

        free(receive_buffer);
    }

    else {
        MPI_Gather(&sum, 1, MPI_INT, NULL, 0, MPI_INT, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}