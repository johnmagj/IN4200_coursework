#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

void deallocate_image(image *u) {
    free(u->image_data[0]);
    free(u->image_data);
}