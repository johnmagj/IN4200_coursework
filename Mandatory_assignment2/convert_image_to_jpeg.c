#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

void convert_image_to_jpeg(const image *u, unsigned char* image_chars) {

    for (int i = 0; i < u->m; i++) {
        for (int j = 0; j < u->n; j++) {

            image_chars[i*u->n + j] = u->image_data[i][j];
        }
    }
}