#include <fstream>

double x_squared_minus_two(double x);
double two_x(double x);

double bisection(double (*f)(double), double a, double b);
double false_position(double (*f)(double), double a, double b);
double newtons_method(double (*f)(double), double (*f_deriv)(double), double x);

bool same_sign(double x, double y);

void log_data(std::ofstream &file, double x, double y);
