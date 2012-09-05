#ifndef RANGE_FIND_H
#define RANGE_FIND_H

#include <stdio.h>
#include <math.h>
#include <float.h>

float find_float_max()
{
    float previous_max = 1.0, max = 1.0;
    float inf = powf(10, 10000);

    for (float delta = 3; delta > 0.0000001; delta /= 2) {
        float d = (delta <= 1) ? (1 + delta) : delta;
        while (max != inf) {
            previous_max = max;
            max *= d;
        }

        max = previous_max;
    }

    return max;
}

double find_double_max()
{
    double previous_max = 1.0, max = 1.0;
    double inf = powf(10, 10000);

    for (double delta = 3; delta > 0.0000001; delta /= 2) {
        double d = (delta <= 1) ? (1 + delta) : delta;
        while (max != inf) {
            previous_max = max;
            max *= d;
        }

        max = previous_max;
    }

    return max;
}

long double find_long_double_max()
{
    long double previous_max = 1.0, max = 1.0;
    long double inf = powf(10, 10000);

    for (long double delta = 3; delta > 0.0000001; delta /= 2) {
        long double d = (delta <= 1) ? (1 + delta) : delta;
        while (max != inf) {
            previous_max = max;
            max *= d;
        }

        max = previous_max;
    }

    return max;
}

void print_ranges()
{
    printf("Real float max:\t\t%.20e\n", FLT_MAX);
    printf("Approximated float max:\t\t%.20e\n", find_float_max());

    printf("Real double max:\t\t%.20e\n", DBL_MAX);
    printf("Approximated double max:\t\t%.20e\n", find_double_max());

    printf("Real long double max:\t\t%.20e\n", LDBL_MAX);
    printf("Approximated long double max:\t\t%.20e\n", find_long_double_max());
}

#endif
