#ifndef X_INTERSECTION_H
#define X_INTERSECTION_H

#include <iostream>
#include <fstream>

#include "x_intersection.h"

using namespace std;

// finds the intersection of function f with the x-axis between values a and b
// uses the bisection method
double bisection(double (*f)(double), double a, double b)
{
    double midpoint = 0;
    double threshold = 0.00000000001; // used to approximate zero

    ofstream data_file("bisection.txt", ios::trunc | ios::out);

    // limit the amount of iterations
    for(int max_iter = 0; max_iter < 1000; ++max_iter) {
        midpoint = (a + b) / 2.0;

        // log data for plotting purposes
        log_data(data_file, max_iter, (*f)(midpoint));

        if ((*f)(midpoint) > -threshold && (*f)(midpoint) < threshold) {
            data_file.close();
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
    data_file.close();
    return midpoint;
}

// finds the intersection of function f with the x-axis between values a and b
// uses the false position method
double false_position(double (*f)(double), double a, double b)
{
    double threshold = 0.00000000001; // used to approximate zero
    double secant_root;

    ofstream data_file("falseposition.txt", ios::trunc | ios::out);

    // limit the number of iterations
    for (int max_iter = 0; max_iter < 1000; ++max_iter) {
        // calculate the root of the secant
        secant_root = ( (*f)(b) * a - (*f)(a) * b) / ( (*f)(b) - (*f)(a) );

        // log data for plotting purposes
        log_data(data_file, max_iter, (*f)(secant_root));

        if ((*f)(secant_root) > -threshold && (*f)(secant_root) < threshold) {
            data_file.close();
            return secant_root;
        }

        if (same_sign((*f)(a), (*f)(secant_root)))
            a = secant_root;
        else
            b = secant_root;
    }
}

// simple function to pass to other functions
double x_squared_minus_two(double x)
{
    return (x * x) - 2;
}

// returns true if both x and y have the same sign (i.e. both positive, both
// negative, or both zero)
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

// logs datapoints into a file using a CSV format
void log_data(ofstream &file, double x, double y)
{
    file << x << ", " << y << endl;
}

#endif
