#ifndef INTEGRATION_FUNCTIONS_H
#define INTEGRATION_FUNCTIONS_H

#include <math.h>

double x_squared(double  x, void *args)
{
    return x * x;
}

double x_to_the_third(double  x, void *args)
{
    return x * x * x;
}

double x_to_the_fourth(double  x, void *args)
{
    return x * x * x * x;
}

double x_to_the_fifth(double  x, void *args)
{
    return x * x * x * x * x;
}

double e_to_minus_x(double  x, void *args)
{
    return exp(-x);
}

double x_e_to_minus_x(double  x, void *args)
{
    return x * exp(-x);
}

double x_to_minus_5(double  x, void *args)
{
    return pow(x, -0.5);
}

#endif
