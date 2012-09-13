#define _USE_MATH_DEFINES
#include <iostream>
#include <float.h>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <map>

#include <gsl_integration.h>

#include "x_intersection.h"
#include "integration_functions.h"

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
double square( double x);
double get_h_value(double *sin_x, int i, int j);
double sin_function(double x);
void print_map(map<string, map<double, approx_slope> > mappie);



int calculate_rightside()
{
    std::cout<<"Calculating the right hand numerical derivative"<<endl;
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
    map<string, map<double, approx_slope> > map_x_h_slope;


    double approx_deriv;

    // Calculate all slopes using the vector values aboven
    for(int i = 0; i < x_size; i++){

        // Try all values of h to differentiate
        for(int j = 0; j < h_size; j ++ ){

            // Calculate slope
            approx_deriv = righthand_side_differentiation(sin_function, sin_x[i],
                                                   values_h[j]);
            map_x_h_slope[str_array[i]][values_h[j]].set_value(approx_deriv,
                                                                actual_derivative[i]);

        }
    }

    // Add special case for the Wikpedia suggestion of sqrt(epsilon) * x
    for(int i = 0; i < x_size; i++){
        double h_value = sqrt(DBL_EPSILON) * sin_x[i];
        approx_deriv = righthand_side_differentiation(sin_function, sin_x[i], h_value);
        map_x_h_slope[str_array[i]][h_value].set_value(approx_deriv,
                                                            actual_derivative[i]);

    }


    print_map(map_x_h_slope);
}


// Print the table
void print_map(map<string, map<double, approx_slope> > mappie)
{
    printf("-----differentiating for different values of f(x) = sin(x)------\n");
    printf("%*s, %*s, %*s, %*s, %*s\n", 20, "value h", 16, "value x", 16, "outcome", 16,
           "actual outcome", 16, "error");
    map<string, map<double, approx_slope> >::iterator it;
    map<double, approx_slope>::iterator it2;
    for(it = mappie.begin(); it != mappie.end(); it++)
    {
        for(it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            printf("%*s, %*.12f %*.12f %*.12f %*.12f\n", 20, it->first.c_str(),
                   16, it2->first, 16, it2->second.approx_deriv, 16,
                   it2->second.actual_deriv, 16,it2->second.error);
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

double square( double x, void *args)
{
    return pow(x, 2);
}

// The sin function that is needed for the first example
double sin_function(double x){
    return sin(x);
}

void question1()
{
    cout << "===== Question 1 =====" << endl;
    calculate_rightside();
    cout << endl;
}

void question2()
{
    cout << "===== Question 2 =====" << endl;

    cout << "Sqrt(2) by interpolation:\t" << bisection(&x_squared_minus_two, 0, 2, true) << endl;
    cout << "Sqrt(2) by regula falsi:\t" << false_position(&x_squared_minus_two, 0, 2, true) << endl;
    cout << "Sqrt(2) by Newton's method:\t" << newtons_method(&x_squared_minus_two, &two_x, 0, true) << endl;
    cout << "To see a graph of each method's convergence, run plot_convergence.py" << endl << endl;
}

void question3()
{
    cout << "===== Question 3 =====" << endl;

    cout << "x^3 - 3x - 2 with x0 = 0: " <<
        newtons_method(&question3_eq1, &question3_eq1_deriv, 0) << endl;

    cout << "x^3 - 3x - 2 with x0 = 5: " <<
        newtons_method(&question3_eq1, &question3_eq1_deriv, 5) << endl;

    cout << "(x^2 + 1)(x − 4) with x0 = -2" <<
        newtons_method(&question3_eq2, &question3_eq2_deriv, -2) << endl;

    cout << "(x^2 + 1)(x − 4) with x0 = 0" <<
        newtons_method(&question3_eq2, &question3_eq2_deriv, 0) << endl;

    cout << endl;
}

void question5()
{
    cout << "===== Question 5 =====" << endl;
    gsl_integration_workspace * w = gsl_integration_workspace_alloc (1000);

    double result, error;
    double alpha = 1.0;

    gsl_function F;
    F.function = &x_squared;
    F.params = &alpha;

    gsl_integration_qags (&F, 0, 1, 0, 1e-7, 1000,
                          w, &result, &error); 
    cout << "Integral of x^2 from 0 to 1 with gsl: " << result << endl;

    F.function = &x_to_the_third;
    gsl_integration_qags (&F, 0, 1, 0, 1e-7, 1000,
                          w, &result, &error); 
    cout << "Integral of x^3 from 0 to 1 with gsl: " << result << endl;

    F.function = &x_to_the_fourth;
    gsl_integration_qags (&F, 0, 1, 0, 1e-7, 1000,
                          w, &result, &error); 
    cout << "Integral of x^4 from 0 to 1 with gsl: " << result << endl;

    F.function = &x_to_the_fifth;
    gsl_integration_qags (&F, 0, 1, 0, 1e-7, 1000,
                          w, &result, &error); 
    cout << "Integral of x^5 from 0 to 1 with gsl: " << result << endl;

    F.function = &e_to_minus_x;
    gsl_integration_qags (&F, 0, 1, 0, 1e-7, 1000,
                          w, &result, &error); 
    cout << "Integral of e^-x from 0 to 1 with gsl: " << result << endl;

    F.function = x_e_to_minus_x;
    gsl_integration_qags (&F, 0, 2, 0, 1e-7, 1000,
                          w, &result, &error); 
    cout << "Integral of xe^-x from 0 to 2 with gsl: " << result << endl;

    F.function = x_e_to_minus_x;
    gsl_integration_qags (&F, 0, 20, 0, 1e-7, 1000,
                          w, &result, &error); 
    cout << "Integral of xe^-x from 0 to 20 with gsl: " << result << endl;

    F.function = x_to_minus_5;
    gsl_integration_qags (&F, 0, 2, 0, 1e-7, 1000,
                          w, &result, &error); 
    cout << "Integral of x^-5 from 0 to 2 with gsl: " << result << endl;

    gsl_integration_workspace_free (w);
    cout << endl;
}

int main(int argc, const char *argv[])
{
    question1();
    question2();
    question3();
    question5();
    
    return 0;
}
