#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {

    // File pointer
    FILE * file;

    // Opening file in read mode ("r")
    file = fopen("ex2a_data.txt", "r");

    if (file == NULL) {
        printf("Error in opening file");
        return 1;
    }

    int *arr = malloc(10*(sizeof(*arr)));

    int hour, minute;
    float temp;

    int hour_max=0, hour_min=0, minute_max=0, minute_min=0;
    float temp_max, temp_min;
    float temp_sum = 0.0;

    int count = 0;
    while (fscanf(file, "%d:%d %f", &hour, &minute, &temp) == 3) {
        printf("%02d:%02d %g \n", hour, minute, temp);

        if (count < 1) {
            temp_max = temp;
            temp_min = temp;
            hour_max = hour;
            hour_min = hour;
            minute_max = minute;
            minute_min = minute;
        }

        if (temp < temp_min) {
            temp_min = temp;
            hour_min = hour;
            minute_min = minute;
        }

        if (temp > temp_max) {
            temp_max = temp;
            hour_max = hour;
            minute_max = minute;
        }

        arr[count] = temp;

        temp_sum += temp;

        count += 1;
    }

    fclose(file);

    float temp_avg = temp_sum/count;

    float res_sum = 0;
    for (int i = 0; i < count; i++) {
        float temp_current = arr[i];
        float diff = temp_current - temp_avg;
        res_sum += diff*diff;
    }

    free(arr);
    arr = NULL;

    float temp_var = res_sum/count;
    float temp_std = sqrt(temp_var);

    printf("Count: %i\n", count);

    printf("Min. temp: %g\n", temp_min);
    printf("Max. temp: %g\n", temp_max);
    printf("Avg. temp: %g\n", temp_avg);
    printf("var. temp: %g\n", temp_var);
    printf("std. temp: %g\n", temp_std);

    return 0;
}

// Done