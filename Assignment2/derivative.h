#ifndef DERIVATIVE_H
#define DERIVATIVE_H

#define _USE_MATH_DEFINES
#include <iostream>
#include <float.h>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <map>

using namespace std;

struct approx_slope{
    void set_value(double app, double act){
        approx_deriv = app;
        actual_deriv = act;
        error = abs(app - act);
    }

    double approx_deriv;
    double actual_deriv;
    double error;
};


double righthand_side_differentiation(double (*f)(double), double x, double h);
double center_differentiation(double (*f)(double), double x, double h);
double square( double x);
double get_h_value(double *sin_x, int i, int j);
double sin_function(double x);
void print_map(map<string, map<double, approx_slope> > mappie);
void calculate_centre();
void calculate_rightside();

#endif
