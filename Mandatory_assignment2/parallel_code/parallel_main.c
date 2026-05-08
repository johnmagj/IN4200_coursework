#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "../function_declarations.h"
#include "../example_folder/simple-jpeg/import_export_jpeg.h"

int main(int argc, char *argv[]) {

    int m, n, c, iters;
    int my_m, my_rank, num_procs;
    float kappa;
    image u, u_bar, whole_image;
    unsigned char *image_chars, *my_image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    // Read from command line and assign to variables
    // Only done by main rank 0
    if (my_rank == 0) {
        kappa = atof(argv[1]);
        iters = atol(argv[2]);
        input_jpeg_filename = argv[3];
        output_jpeg_filename = argv[4];
  
        import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);
    }

    MPI_Bcast(&m, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast (&iters, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast (&kappa, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

    printf("myrank: %d, m = %d\n", my_rank, m);

    // Horizontal decomposition of image matrix
    int minimum_rows_per_rank = m/num_procs;
    int remaining_rows = m % num_procs;

    int *total_rows_per_rank = malloc(num_procs*sizeof(*total_rows_per_rank));
    int *send_counts = malloc(num_procs*sizeof(*total_rows_per_rank));
    int *send_displacement = malloc(num_procs*sizeof(*total_rows_per_rank));

    int *recv_total_rows_per_rank = malloc(num_procs*sizeof(*total_rows_per_rank));
    int *recv_counts = malloc(num_procs*sizeof(*total_rows_per_rank));
    int *recv_displacement = malloc(num_procs*sizeof(*total_rows_per_rank));   

    int first_rank_with_one_extra_row = num_procs - remaining_rows;
    int displacement_counter = 0;
    for (int rank = 0; rank < num_procs; rank++) {

        // Let the remaining rows be handled by the last ranks (one each), potentially by rank 1 and onwards
        int numb_rows_this_rank = minimum_rows_per_rank + (rank >= first_rank_with_one_extra_row);

        // Calculate counts and displacement with no halo rows
        total_rows_per_rank[rank] = numb_rows_this_rank;
        recv_total_rows_per_rank[rank] = numb_rows_this_rank;
        int counts = numb_rows_this_rank*n;
        send_counts[rank] = counts;
        recv_counts[rank] = counts;
        send_displacement[rank] = displacement_counter;
        recv_displacement[rank] = displacement_counter;
        displacement_counter += counts;

        // Adjust displacement to add one more row bellow the first rank, and one more row above the last rank, 
        // the rest gets two rows extra, one above and one bellow.
        // If only 1 process, no halo
        if (num_procs > 1) {
            if (rank == 0) {
                total_rows_per_rank[rank] += 1;
                send_counts[rank] += n;
            }    
            else if (rank == num_procs-1) {
                total_rows_per_rank[rank] += 1;
                send_counts[rank] += n;
                send_displacement[rank] -= n;
            }
            else {
                total_rows_per_rank[rank] += 2;
                send_counts[rank] += 2*n;
                send_displacement[rank] -= n;
            }
        }
    }

    my_m = total_rows_per_rank[my_rank];

    allocate_image(&u, my_m, n);
    allocate_image(&u_bar, my_m, n);

    my_image_chars = malloc(send_counts[my_rank]*sizeof(*my_image_chars));
        
    MPI_Scatterv(image_chars,
                 send_counts,
                 send_displacement,
                 MPI_UNSIGNED_CHAR,
                 my_image_chars,
                 send_counts[my_rank],
                 MPI_UNSIGNED_CHAR,
                 0,
                 MPI_COMM_WORLD);

    convert_jpeg_to_image (my_image_chars, &u);
    iso_diffusion_denoising_parallel (&u, &u_bar, kappa, iters);

    // Must be allocated in all processes to work with MPI_Gatherv
    allocate_image(&whole_image, m, n);

    MPI_Gatherv(&u_bar.image_data[0][0],
                recv_counts[my_rank],
                MPI_FLOAT,
                &whole_image.image_data[0][0],
                recv_counts,
                recv_displacement,
                MPI_FLOAT,
                0,
                MPI_COMM_WORLD);

    if (my_rank == 0) {
        convert_image_to_jpeg(&whole_image, image_chars);
        export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);   
    }

    deallocate_image (&whole_image);

    free(total_rows_per_rank);
    free(send_counts);
    free(send_displacement);

    free(recv_total_rows_per_rank);
    free(recv_counts);
    free(recv_displacement);
    
    MPI_Finalize();

    return 0;
}