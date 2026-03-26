#include <stdio.h>
#include <stdlib.h>

void swap(double *elem_A, double *elem_B) {

    double new_A = *elem_B;
    double new_B = *elem_A;

    *elem_A = new_A;
    *elem_B = new_B;
}

int main() {

    double arr[] = {4.0, 3.0, 2.0, 1.0};

    int n = 4;

    int num_swaps;
    int counter = 0;
    do {
        num_swaps = 0;
        for (int i = 0; i < n - 1; i++) {
            // If even index
            if (i%2 == 0) {
                for (int j = 0; j < n - 1; j+=2) {
                    if (arr[j] > arr[j+1]) {
                        swap(&arr[j], &arr[j+1]);
                        num_swaps += 1;
                    }
                }
                }
            // If odd index
            else {
                for (int j = 1; j < n - 1; j+=2) {
                    if (arr[j] > arr[j+1]) {
                        swap(&arr[j], &arr[j+1]);
                        num_swaps += 1;
                    }
                }       
            }
        }

        for (int i = 0; i < n; i++) {
            printf("%g ", arr[i]);
        }
        printf("\n");

        counter += 1;
    } while (num_swaps > 0);

    printf("%d", counter);

    return 0;
}