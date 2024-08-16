#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <tgmath.h>

// see https://en.wikipedia.org/wiki/Numerical_differentiation
float derivitive(double f(double), double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

int main(void) {
    
    double h = 10.;
    int max_h_divisions = 10;
    double range_start = 0.;
    double range_end = 1.;
    double range_inc = 0.01;
    double range_size = (range_end - range_start) / range_inc;

    for (int i = 1; i < max_h_divisions; ++i) {
        h /= 10;
        printf("h (precision): %e\t", h);

        double accumulated_error = 0.;  

        // if f = sin, f' = cos

        for (double x = range_start; x < range_end; x += range_inc) {
            double pred_y = derivitive(sin, x, h);
            double expected_y = cos(x);
            accumulated_error += fabs(expected_y - pred_y);
        }

        accumulated_error /= range_size;

        printf("error = %e\n", accumulated_error);
    }
}
