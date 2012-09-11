#include <iostream>

#include "x_intersection.h"

using namespace std;

// finds the intersection of function f with the x-axis between values a and b
// uses the bisection method
double bisection(double (*f)(double), double a, double b)
{
    double midpoint = 0;
    double threshold = 0.00000001; // used to approximate zero

    // limit the amount of iterations
    for(int max_iter = 0; max_iter < 1000; ++max_iter) {
        midpoint = (a + b) / 2.0;

        if ((*f)(midpoint) > -threshold && (*f)(midpoint) < threshold) {
            return midpoint;
        }

        // if f(a) and f(midpoint) have the same sign, replace a with midpoint
        if (same_sign( (*f)(a), (*f)(midpoint)) )
            a = midpoint;
        else
            b = midpoint;
    }

    // if no solution has been found in the maximum number of iteration, return
    // the latest value and hope for the best
    return midpoint;
}

// simple function to pass to other functions
double x_squared_minus_two(double x)
{
    return (x * x) - 2;
}

bool same_sign(double x, double y)
{
    if ((x < 0) && (y < 0))
        return true;
    if ((x > 0) && (y > 0))
        return true;
    if ((x == 0) && (y == 0))
        return true;

    return false;
}
