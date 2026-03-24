#include <stdio.h>
#include <stdlib.h>

int main() {

    // int *ptr = NULL;
    // int n = 5;

    // ptr = (int*) malloc(n * sizeof(int));

    // if (ptr == NULL) {
    //     printf("Error");
    // }

    // for (int i = 0; i < n; i++) {

    //     ptr[i] = i;

    //     printf("%d\n", ptr[i]);
    // }

    // printf("\n");

    //     for (int i = 0; i < n; i++) {

    //         printf("%p\n", *(ptr + i));
    //     }

    // free(ptr);


    // int a[5] = {1,2, [4]=10};

    // int *ptr = a;

    // for (int i = 0; i < 5; i++) {
    //     printf("%p\n", &a[i]);
    //     printf("%d and %d\n", ptr[i], a[i]);
    //     printf("%p\n\n", &ptr[i]);
    // }

    // printf("%p", &ptr);

    // printf("%i", sizeof(ptr));

    //printf("%p  ", ptr);

    // printf("%d", sizeof(*ptr));

    // int *ptr_arr = malloc(5*sizeof(ptr_arr));

    // for (int i = 0; i < 5; i++) {
    // printf("%p\n", (void*)&ptr_arr[i]);
    // }

    // free(ptr_arr);

    int a[5] = {1, 2};

    for (int i = 0; i < 5; i++) {
        printf("%d\n", a[i]);
    }

    return 0;

}