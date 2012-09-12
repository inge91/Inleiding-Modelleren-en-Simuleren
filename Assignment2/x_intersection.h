#include <fstream>

double x_squared_minus_two(double x);
double bisection(double (*f)(double), double a, double b);

bool same_sign(double x, double y);

void log_data(std::ofstream &file, double x, double y);
