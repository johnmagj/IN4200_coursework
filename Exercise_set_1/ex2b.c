#include <stdio.h>
#include <stdlib.h>

void smooth(double *v_new, double *v, int n, double c) {
    int i;
    for (i = 0; i < n-1; i++){
        v_new = v[i] + c*(v[i] - 2*v[i] + v[i+1]);
    }
}