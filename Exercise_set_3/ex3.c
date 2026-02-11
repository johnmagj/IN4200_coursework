#include <stdio.h>
#include <math.h>
#include <time.h>

double my_pow_func(double x, double y) {

    double prod = x;

    for (int i = 1; i < y; i++) {

        prod = prod*x;

    }

    return prod;
}

int main() {
    clock_t t_start, t_stop;
    double x = 2.0;
    double y = 100.0;

    t_start = clock();
    double my_pow = my_pow_func(x, y);
    t_stop = clock();
    double my_time = (t_stop - t_start)/CLOCKS_PER_SEC;

    t_start = clock();
    double lib_pow = pow(x, y);
    t_stop = clock();
    double lib_time = (t_stop - t_start)/CLOCKS_PER_SEC;

    printf("My answ: %lf, in %lf", my_pow, my_time);
    printf("\n");
    printf("Lib answ: %lf, in %lf", lib_pow, lib_time);

    return 0;
}