#define _USE_MATH_DEFINES
#include <iostream>
#include <float.h>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <map>

using namespace std;
double righthand_side_differentiation(double (*f)(double), double x, double h);
double square( double x);
double get_h_value(double *sin_x, int i, int j);
double sin_function(double x);
void print_map(map<double, map<double, double> > mappie);

int main()
{
    // different values for x to try
    double sin_x[] = {M_PI / 3, 100 * M_PI + M_PI/3,
                      pow(10, 12) * M_PI + M_PI / 3};


    string str_array[] = {"pi / 3", "100 * pi + pi / 3",
                                "10^12 * pi + pi / 3"};

    double values_h[] = {1, 0.1, 0.000001, DBL_EPSILON};

    // Derivative made by solving h goint to 0
    double actual_derivative[] = {0.5, cos(sin_x[1]), cos(sin_x[2])};

    int x_size = sizeof sin_x / sizeof(double);
    int h_size = sizeof values_h / sizeof(double);

    // Making a map with first key x, second key h
    map<double, map<double, double> > map_x_h_slope;


    double slope;

    // Calculate all slopes using the vector values aboven
    for(int i = 0; i < x_size; i++){

        // Try all values of h to differentiate
        for(int j = 0; j < h_size; j ++ ){

            // Calculate slope
            slope = righthand_side_differentiation(sin_function, sin_x[i],
                                                   values_h[j]);
            map_x_h_slope[sin_x[i]][values_h[j]] = slope;

        }
    }

    // Add special case for the Wikpedia suggestion of sqrt(epsilon) * x
    for(int i = 0; i < x_size; i++){
        double h_value = sqrt(DBL_EPSILON) * sin_x[i];
        slope = righthand_side_differentiation(sin_function, sin_x[i], h_value);
        map_x_h_slope[sin_x[i]][h_value] = slope;
    }
/*
    printf("-----differentiating for different values of f(x) = sin(x)------\n");
    printf("value h \t\t value x \t\t outcome \t\t actual outcome"
           "\t\terror\n\n");
    printf("%.12f\t\t",get_h_value(sin_x, i, j));
    printf("%s\t\t", str_array[i].c_str());
    printf("%.12f\t\t", slope);
    printf("%.12f\t\t", actual_derivative[i]);
    printf("%.12f\t\t", abs(actual_derivative[i] - slope));

    return 0;
*/

    print_map(map_x_h_slope);
}


// Print the table
void print_map(map<double, map<double, double> > mappie)
{
    printf("-----differentiating for different values of f(x) = sin(x)------\n");
    printf("value h \t\t value x \t\t outcome \t\t actual outcome"
           "\t\terror\n\n");
    map<double, map<double, double> >::iterator it;
    map<double, double>::iterator it2;
    for(it = mappie.begin(); it != mappie.end(); it++)
    {
        for(it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            printf("%.12f, ---- %.12f ----- %.12f\n", it->first,
                   it2->first, it2->second);
        }
    }

}

// Finding the slope of two points using finite distance approach
double righthand_side_differentiation(double (*f)(double), double x, double h)
{
    double xph;
    double dx;

    // Make sure you work with the same h (when h is small)
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
double sin_function(double x){
    return sin(x);
}
