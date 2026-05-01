#include <stdlib.h>
#include "function_declarations.h"

void allocate_image(image *u, int m, int n) {
    u->m = m;
    u->n = n;

    u->image_data = malloc(m*sizeof(*u->image_data));
    u->image_data[0] = malloc(m*n*sizeof(*u->image_data[0]));

    for (int i = 1; i < m; i++) {
        u->image_data[i] = &(u->image_data[0][i*n]);
    }
}