#include <stdio.h>
#include <stdlib.h>

long trailing(const int max) {
    //factorials are a series of iterative
    //multiplications made of factors.
    //if we identify the factors that make trailing
    //zeros (2s 5s & 10s) we can find the number of
    //trailing zeros
    long twos = 0, fives = 0, tens = 0;
    //iteration through values
    for (long i = 1; i <= max; ++i) {
        long x = i;
        //find the number of 10s 5s and twos by
        //repetitive division
        while (x % 10 == 0) {
            tens++;
            x /= 10;
        }
        while (x % 5 == 0) {
            fives++;
            x /= 5;
        }
        while (x % 2 == 0) {
            twos++;
            x /= 2;
        }
    }
    //the number of 0s is the number of 10s
    //plus the mininum of the fives and twos
    //since they pair up to make tens
    return tens + (fives < twos ? fives : twos);
}

int main() {
    long x = 0;
    scanf("%ld", &x);
    printf("%ld\n", trailing(x));
    return 0;
}