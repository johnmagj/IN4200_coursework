#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "function_declarations.h"

void iso_diffusion_denoising_parallel(image *u, image *u_bar, float kappa, int iters) {

    // Get rank and total number of processes from parallel_main 
    int my_rank, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    for (int iter = 0; iter < iters; iter++) {
        for (int i = 0; i < u->m; i++) {
            for (int j = 0; j < u->n; j++) {

                // Boundary conditions, copy the frame of u directly to u_bar 
                if (i == 0) {

                    // Fill in top row of image
                    if (my_rank == 0) {
                        u_bar->image_data[i][j] = u->image_data[i][j];
                    }
                    else {
                        // Pass
                    }
                }
                
                else if (i == u->m - 1) {
                    
                    // Fill in bottom row of image
                    if (my_rank == num_procs - 1) {
                        u_bar->image_data[i][j] = u->image_data[i][j];
                    }
                    else {
                        // Pass
                    }
                }

                else if (j == 0 || j == u->n - 1) {
                    u_bar->image_data[i][j] = u->image_data[i][j];
                }

                else {
                    u_bar->image_data[i][j] = u->image_data[i][j] + 
                                            kappa*(u->image_data[i-1][j] + 
                                                u->image_data[i][j-1] - 
                                                4*u->image_data[i][j] + 
                                                u->image_data[i][j+1] + 
                                                u->image_data[i+1][j]);
                }
            }
        }

        if (my_rank == 0) {
            MPI_Sendrecv(&u->image_data[u->m-2][0],
                         u->n,
                         MPI_FLOAT,
                         1,
                         0,
                         &u->image_data[u->m-1][0],
                         u->n,
                         MPI_FLOAT,
                         1,
                         0,
                         MPI_COMM_WORLD,
                         MPI_STATUS_IGNORE);
        }
        else if (my_rank == num_procs - 1) {
            MPI_Sendrecv(&u->image_data[1][0],
                         u->n,
                         MPI_FLOAT,
                         my_rank-1,
                         0,
                         &u->image_data[0][0],
                         u->n,
                         MPI_FLOAT,
                         my_rank-1,
                         0,
                         MPI_COMM_WORLD,
                         MPI_STATUS_IGNORE);
        }
        else {
            // Upward send
            MPI_Sendrecv(&u->image_data[1][0],
                         u->n,
                         MPI_FLOAT,
                         my_rank-1,
                         0,
                         &u->image_data[0][0],
                         u->n,
                         MPI_FLOAT,
                         my_rank-1,
                         0,
                         MPI_COMM_WORLD,
                         MPI_STATUS_IGNORE);

            // Downward send
                        MPI_Sendrecv(&u->image_data[u->m-2][0],
                         u->n,
                         MPI_FLOAT,
                         my_rank+1,
                         0,
                         &u->image_data[u->m-1][0],
                         u->n,
                         MPI_FLOAT,
                         my_rank+1,
                         0,
                         MPI_COMM_WORLD,
                         MPI_STATUS_IGNORE);
        }

        // Pointer swap, not for last iteration making u_bar->image_data last version
        if (iter < iters - 1) {
            float **temp = u->image_data;
            u->image_data = u_bar->image_data;
            u_bar->image_data = temp;
        }
        // printf("iter: %d/%d\n", iter+1, iters);
    }
}