#include <fstream>

double x_squared_minus_two(double x);
double two_x(double x);
double question3_eq1(double x);
double question3_eq1_deriv(double x);
double question3_eq2(double x);
double question3_eq2_deriv(double x);

double bisection(double (*f)(double), double a, double b,
                 bool logging_enabled=false);

double false_position(double (*f)(double), double a, double b,
                      bool logging_enabled=false);

double newtons_method(double (*f)(double), double (*f_deriv)(double), double x,
                      bool logging_enabled=false);

bool same_sign(double x, double y);

void log_data(std::ofstream &file, double x, double y, bool logging_enabled);
