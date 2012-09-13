#ifndef X_INTERSECTION_H
#define X_INTERSECTION_H

#include <iostream>
#include <fstream>
#include <cmath>

#include "x_intersection.h"

using namespace std;

// finds the intersection of function f with the x-axis between values a and b
// uses the bisection method
double bisection(double (*f)(double), double a, double b, bool logging_enabled)
{
    double midpoint = 0;
    double threshold = 0.00000000000001; // used to approximate zero

    ofstream data_file("bisection.txt", ios::trunc | ios::out);

    // limit the amount of iterations
    for(int max_iter = 0; max_iter < 1000; ++max_iter) {
        midpoint = (a + b) / 2.0;

        // log data for plotting purposes
        log_data(data_file, max_iter, abs( (*f)(midpoint) ), logging_enabled);

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
double false_position(double (*f)(double), double a, double b, bool logging_enabled)
{
    double threshold = 0.00000000000001; // used to approximate zero
    double secant_root;

    ofstream data_file("falseposition.txt", ios::trunc | ios::out);

    // limit the number of iterations
    for (int max_iter = 0; max_iter < 1000; ++max_iter) {
        // calculate the root of the secant
        secant_root = ( (*f)(b) * a - (*f)(a) * b) / ( (*f)(b) - (*f)(a) );

        // log data for plotting purposes
        log_data(data_file, max_iter, abs( (*f)(secant_root) ), logging_enabled);

        if ((*f)(secant_root) > -threshold && (*f)(secant_root) < threshold) {
            data_file.close();
            return secant_root;
        }

        if (same_sign((*f)(a), (*f)(secant_root)))
            a = secant_root;
        else
            b = secant_root;
    }

    // if no solution has been found in the maximum number of iteration, return
    // the latest value and hope for the best
    data_file.close();
    return secant_root;
}

// finds the intersection of function f with the x-axis between values a and b
// uses Newton's method
// 
// f = function to find the root of
// f_deriv = the derivative of f
// x = the starting point for the algorithm
double newtons_method(double (*f)(double), double (*f_deriv)(double), double x, bool logging_enabled)
{
    double threshold = 0.00000000000001; // used to approximate zero

    ofstream data_file("newtonsmethod.txt", ios::trunc | ios::out);

    // limit the number of iterations
    for (int max_iter = 0; max_iter < 1000; ++max_iter) {
        // log data for plotting purposes
        log_data(data_file, max_iter, abs( (*f)(x) ), logging_enabled);

        if ((*f)(x) > -threshold && (*f)(x) < threshold) {
            data_file.close();
            return x;
        }

        // make sure we don't divide by zero
        if ((*f_deriv)(x) == 0) {
            x += 1;
            continue;
        }

        x -= (*f)(x) / (*f_deriv)(x);
    }

    // if no solution has been found in the maximum number of iteration, return
    // the latest value and hope for the best
    data_file.close();
    return x;
}

// simple function to pass to other functions
double x_squared_minus_two(double x)
{
    return (x * x) - 2;
}

// derivative of x_squared_minus_two
double two_x(double x)
{
    return 2 * x;
}

// first equation of question 3
double question3_eq1(double x)
{
    return (x * x * x) - 3 * x - 2;
}

double question3_eq1_deriv(double x)
{
    return 3 * (x * x) - 3;
}

// second equation of question 3
double question3_eq2(double x)
{
    return ( (x*x) + 1) * (x - 4);
}

double question3_eq2_deriv(double x)
{
    return ( (2 * x) * (x - 4) ) + (x*x  + 1);
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
void log_data(ofstream &file, double x, double y, bool logging_enabled)
{
    if (logging_enabled)
        file << x << ", " << y << endl;
}

#endif
