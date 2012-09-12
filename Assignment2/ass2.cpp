#define _USE_MATH_DEFINES
#include <iostream>
#include <float.h>
#include <vector>
#include <cmath>

using namespace std;
double righthand_side_differentiation(double (*f)(double), double x, double h);
double square( double x);

int main()
{
    // different values for x to try
    double sin_x[] = {M_PI / 3, 100 * M_PI + M_PI/3, pow(10, 12) * M_PI + M_PI / 3};
    double values_h[] = {0.000001, 0.1, 1, 0.0000000000000000001};
    double square_x [] = { 1 };

    int size_x, size_h;
    // determine the size of the arrays
    size_h = sizeof values_h/sizeof(double);
    size_x = sizeof square_x/sizeof(double);

    double slope;

    // Trye all values of h to differentiate
    for(int i = 0; i < size_h; i++){

        // Try all values of x to differentiate
        for(int j = 0; j < size_x; j ++ ){
            slope = righthand_side_differentiation(square, sin_x[j], sqrt(DBL_EPSILON) * sin_x[j]);
        }
    }
    std::cout<<slope;

    return 0;

}



// Finding the slope of two points using finite distance approach
double righthand_side_differentiation(double (*f)(double), double x, double h)
{

    double xph;
    double dx;

    // Make sure you work with the same h
    xph = (x + h);
    dx = xph - x;
    double slope = ((*f)(xph) -  (*f)(x)) / dx ;

    return slope;
}

// Finding the slope of two  points around x using finite distance approachs
double center_differentiation(double (*f)(double), double x, double h)
{
     double xph;
     double xmh;
     double dx;

     // Make sure you work with the same h
     xph = (x + h);
     xmh = (x - h);
     dx = xph - x;


     double slope = ((*f)(xph) -  (*f)(x)) / dx ;
     return slope;

}

double square( double x)
{
    return pow(x, 2);
}

// The sin function that is needed for the first example
double sin(double x){
    return sin(x);
}
