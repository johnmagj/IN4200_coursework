#include <stdio.h>
#include <stdlib.h>

void swap(double *elem_A, double *elem_B) {

    double new_A = *elem_B;
    double new_B = *elem_A;

    *elem_A = new_A;
    *elem_B = new_B;
}

void odd_even_sort_array(int n, double *arr) {
    // Sort array

    for (int i = 0; i < (n+1)/2; i++) {
        // For the odd indices
        for (int j = 1; j < n - 1; j+=2) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }

        // If even index
        for (int j = 0; j < n - 1; j+=2) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }      
        }
    }
}

int main() {

    double arr[] = {6.0, 5.0, 4.0, 3.0, 2.0, 1.0};

    int n = sizeof(arr) / sizeof(arr[0]);

    odd_even_sort_array(n, arr);

    for (int i = 0; i < n; i++) {
        printf("%g ", arr[i]);
    }

    return 0;
}