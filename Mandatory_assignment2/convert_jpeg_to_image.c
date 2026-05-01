#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

void convert_jpeg_to_image(const unsigned char* image_chars, image *u) {

    for (int i = 0; i < u->m; i++) {
        for (int j = 0; j < u->n; j++) {
            // printf("%c\n", image_chars[i*u->n + j]);
            u->image_data[i][j] = (float) image_chars[i*u->n + j];
            // printf("%f\n", u->image_data[i][j]);
            // break;
        }
        // break;
    }
}