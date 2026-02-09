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

    for(int i = 0; i < n; i++) {

        arr[i] = rand();

        // Print the array element immediately
        printf("a[%d] = %d\n", i, arr[i]);

    }
    
    return 0;
}