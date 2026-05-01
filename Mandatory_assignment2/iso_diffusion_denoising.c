#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

void iso_diffusion_denoising(image *u, image *u_bar, float kappa, int iters) {
    
    for (int iter = 0; iter < iters; iter++) {
        for (int i = 0; i < u->m; i++) {
            for (int j = 0; j < u->n; j++) {

                // Boundary conditions, copy the frame of u directly to u_bar 
                if (i == 0 || i == u->m - 1 || j == 0 || j == u->n - 1) {
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

        // Pointer swap, not for last iteration making u_bar->image_data last version
        if (iter < iters - 1) {
            float **temp = u->image_data;
            u->image_data = u_bar->image_data;
            u_bar->image_data = temp;
        }
        printf("iter: %d/%d\n", iter+1, iters);
    }
}