#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

    clock_t start, stop;

    double time_bin, time_txt;

    FILE *fp_bin, *fp_txt;


    for(int i = 0; i <= 10; i++) {

        int random_int = rand() % 2;

        printf("%d\n", random_int);

    }

    return 0;
}

/* Remember to Free data */