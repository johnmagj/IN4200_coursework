#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    // Seed rand with current time
    srand(time(NULL));

    int n;

    printf("Enter length of array: ");
    scanf("%d", &n);

    int arr[n];

    for (int i = 0; i < n; i++) {

        arr[i] = rand();

        // Print the array element immediately
        printf("a[%d] = %d\n", i, arr[i]);
    }

    int elem_min = arr[0];
    int elem_max = arr[0];

    int elem_min_indx = 0;
    int elem_max_indx = 0;

    for (int i = 1; i < n; i++) {

        if (arr[i] < elem_min) {

            elem_min = arr[i];
            elem_min_indx = i;
        }
    
        if (arr[i] > elem_max) {

            elem_max = arr[i];
            elem_max_indx = i;
        }
    }

    printf("Minimum value: %i, at index: %i \n", elem_min, elem_min_indx);
    printf("Maximum value: %i, at index: %i", elem_max, elem_max_indx);

    return 0;
}

// Done