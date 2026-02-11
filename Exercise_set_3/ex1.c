#include <stdio.h>
#include <math.h>

double f(double x) {
    return 4.0/(1 + x*x);
}

double numerical_integration(double x_min, double x_max, int slices) {

    double delta_x = (x_max - x_min)/slices;
    double x, sum = 0.0;

    for (int i = 0; i < slices; i++) {

        x = x_min + (i + 0.5)*delta_x;
        sum = sum + f(x);
    }

    return sum*delta_x;
}

int main() {

    for (int i = 1; i <= 5; i++) {
        
        double F = numerical_integration(0.0, 1.0, i); 
        printf("Slices: %d --> %.16g\n", i, F);

        if (fabs(F - M_PI) < 1e-14) {

            printf("i = %d", i);
            break;
        }
    }
    
    double pi = M_PI;

    printf("Approx. pi: %.16g", pi);

    return 0;
}