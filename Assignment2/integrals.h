#ifndef INTEGRALS_H
#define INTEGRALS_H

#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <vector>

typedef double (*fptr)(double);

double rectangle_rule(double interval_min, double interval_max,int subsection_amount,
               double (*f)(double));
double int1(double);
double int2(double);
double int3(double);
double int4(double);
double int5(double);
double int6(double);
double int7(double);
double int8(double);
void ass4();

double trapezoidal_rule(double interval_min, double interval_max,
                        int subsection_amount, double(*f)(double));
double simpsons_rule(double interval_min, double interval_max,
            int subsection_amount, double (*f)(double));
double two_point_gauss(double interval_min, double interval_max,
                int subsection_amount, double (*f)(double));


#endif // INTEGRALS_H
