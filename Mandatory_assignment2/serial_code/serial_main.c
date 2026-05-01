#include <stdio.h>
#include <stdlib.h>
#include "../function_declarations.h"
#include "../example_folder/simple-jpeg/import_export_jpeg.h"

int main(int argc, char *argv[]) {

    int m, n, c, iters;
    float kappa;
    image u, u_bar;
    unsigned char *image_chars;
    char *input_jpeg_filename, *output_jpeg_filename;

    // Read from command line and assign to variables
    kappa = atof(argv[1]);
    iters = atol(argv[2]);
    input_jpeg_filename = argv[3];
    output_jpeg_filename = argv[4];

    printf("%f\n", kappa);
    printf("%d\n", iters);
    printf("%s\n", input_jpeg_filename);
    printf("%s\n", output_jpeg_filename);

    import_JPEG_file(input_jpeg_filename, &image_chars, &m, &n, &c);

    printf("%d\n", c);

    allocate_image(&u, m, n);
    allocate_image(&u_bar, m, n);
    // Fill the empty 2d array u->image_data with the values from the 1d array image_chars
    printf("Start converting from jpeg to image --> ");
    convert_jpeg_to_image (image_chars, &u);
    printf("DONE\n");

    iso_diffusion_denoising(&u, &u_bar, kappa, iters);

    convert_image_to_jpeg (&u_bar, image_chars);
    export_JPEG_file(output_jpeg_filename, image_chars, m, n, c, 75);

    deallocate_image(&u);
    deallocate_image(&u_bar);

    return 0;
}