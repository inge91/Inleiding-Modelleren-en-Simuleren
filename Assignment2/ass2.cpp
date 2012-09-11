#define _USE_MATH_DEFINES
#include <iostream>
#include <float.h>
#include <vector>
#include <cmath>

using namespace std;



void main()
{
    // different values for x to try
    double sin_x[] = {M_PI / 3, 100 * M_PI + M_PI/3, pow(10, 12) * M_PI + M_PI / 3};

    for(int i = 0; i < length(sin_x); i ++ ){

    }

}



// Finding the slope of two points using finite distance approach
void numerical_differentation(double (*f)(double), double x)
{

    double phx;
    double dx;
    // First is the choice of h (the increment)
    // smallest possible interval around x
    h = sqrt(DBL_EPSILON) * x;
    xph += (x + h);
    slope = ((*f)(xph) -  (*f)(x)) / dx ;
}


// The sin function that is needed for the first example
double sin(double x){
    
    return sin(x);
}
