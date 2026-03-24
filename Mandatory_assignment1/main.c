#include <stdio.h>
#include <stdlib.h>
#include "function_declarations.h"

int main(int nargs, char **args) {

    char filename_path[256];

    printf("Enter relative file path to the .mtx file:");
    scanf("%s", &filename_path);
    
    printf("%s", filename_path);

    return 0;
}