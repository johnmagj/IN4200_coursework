#include <stdio.h>
#include <math.h>

double frac(double exponent) {
    return (1.0/pow(2.0, exponent));
}

int main() {

    int i;
    int sign; 

    double sum = 0.0;

    for(i = 0; i <= 1000; i++) {

        if(i%2 != 0) {
            sign = -1;
        }

        else {
            sign = 1;
        }
        
        sum += sign*frac(2.0*i);

        printf("%.16f\n", sum);

        if(fabs(sum-(4.0/5.0)) < 1e-15) {
            printf("i = %d", i);
            break;
        }
    }

    return 0;
}