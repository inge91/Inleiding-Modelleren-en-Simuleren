#define _USE_MATH_DEFINES
#include <iostream>
#include <float.h>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <map>

#include <gsl_integration.h>

#include "derivative.h"
#include "x_intersection.h"
#include "integrals.h"
#include "integration_functions.h"

using namespace std;


void question1()
{
    cout << "===== Question 1 =====" << endl;
    calculate_rightside();
    calculate_centre();
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

void question4()
{
    cout << "===== Question 4 =====" << endl;
    ass4();

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
    question4();
    question5();
    
    return 0;
}

