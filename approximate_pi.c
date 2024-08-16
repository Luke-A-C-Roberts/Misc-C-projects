#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double approximate_pi(double increment) {
    const long square_count = (long)pow(2. * (1. / increment), 2.);
    long circle_count = 0;
    for (double y = -1.; y < 1.; y += increment) {
        for (double x = -1.; x < 1.; x += increment) {
            if (pow(x, 2.) + pow(y, 2.) < 1.) circle_count++;
        } 
    }
    printf("S = %ld, C = %ld\n", square_count, circle_count);
    return 4. * circle_count / square_count;
}

int main(void) {
    for (int i = 1; i < 12; ++i) {
        double increment = 1. / pow(2., (double)i);
        double pi = approximate_pi(increment);
        printf("inc = %f,\tpi = %f\n\n", increment, pi);
    }    

    return EXIT_SUCCESS;
}

