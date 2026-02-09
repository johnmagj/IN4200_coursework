#include <stdio.h>
#include <math.h>

int main() {

    double term = 1.0;
    double sum = 1.0;


    for(int i = 1; i <= 100; i++) {

        // Each term is 1/4 of the pervious term, 
        // By multiplying with -1.0 each iteration we flip the sing, thus no need for if-test.

        term *= -0.25;

        sum += term;
        
        printf("%.16f\n", sum);

        if(fabs(sum-(4.0/5.0)) < 1e-14) {
            printf("i = %d", i);
            break;
        }
    }

    return 0;
}
