#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int nargs, char **args) {

    int size, my_rank;
    MPI_Status status;

    // Initialize parallel region
    MPI_Init(&nargs, &args);

    // Total number of processes running parallel, function assigning to size
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // The unique ID (rank) of the current process
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // Buffer for the message string
    int str_buffer = 256;
    char msg[str_buffer];
    
    // Create variable of message string with format specifier, ready for printing 
    sprintf(msg, "Hello world, from rank: %d!", my_rank);

    // Calculate the (exactly) need message buffer used by MPI Send and Recv
    int msg_buffer = strlen(msg) + 1;
    
    if (my_rank == 0) {

        for (int i = 1; i < size; i++) {
            // Check incoming rank
            MPI_Probe(MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

            MPI_Get_count(&status, MPI_CHAR, &msg_buffer);

            // Using MPI_ANY_SOURCE prevent the loop waiting for a given rank i, if rank i is not ready yet
            MPI_Recv(msg, msg_buffer, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            
            // Since we dont know which rank the message came we find it and store it
            int rank_of_sender = status.MPI_SOURCE;

            printf("I am rank %d and this is a message from rank %d: %s\n", my_rank, rank_of_sender, msg);
        }
    }

    else {
        MPI_Send(msg, msg_buffer, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    // End parallel region
    MPI_Finalize();

    return 0;
}