#include "derivative.h"





void calculate_rightside()
{
    std::cout<<"Calculating the right hand numerical derivative"<<endl;
    // different values for x to try
    double sin_x[] = {M_PI / 3, 100 * M_PI + M_PI/3,
                      pow(10, 12) * M_PI + M_PI / 3};


    string str_array[] = {"pi / 3", "100 * pi + pi / 3",
                                "10^12 * pi + pi / 3"};

    double values_h[] = {1, 0.1, 0.000001, 0.0000001};

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

void calculate_centre()
{
    std::cout<<"Calculating the center derivative"<<endl;
    // different values for x to try
    double sin_x[] = {M_PI / 3, 100 * M_PI + M_PI/3,
                      pow(10, 12) * M_PI + M_PI / 3};


    string str_array[] = {"pi / 3", "100 * pi + pi / 3",
                                "10^12 * pi + pi / 3"};

    double values_h[] = {1, 0.1, 0.000001, 0.0000001};

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
            approx_deriv = center_differentiation(sin_function, sin_x[i],
                                                   values_h[j]);
            map_x_h_slope[str_array[i]][values_h[j]].set_value(approx_deriv,
                                                                actual_derivative[i]);

        }
    }

    // Add special case for the Wikpedia suggestion of sqrt(epsilon) * x
    for(int i = 0; i < x_size; i++){
        double h_value = sqrt(DBL_EPSILON) * sin_x[i];
        approx_deriv = center_differentiation(sin_function, sin_x[i], h_value);
        map_x_h_slope[str_array[i]][h_value].set_value(approx_deriv,
                                                            actual_derivative[i]);

    }


    print_map(map_x_h_slope);
}



// Print the table
void print_map(map<string, map<double, approx_slope> > mappie)
{
    printf("-----differentiating for different values of f(x) = sin(x)------\n");
    printf("%*s, %*s, %*s, %*s, %*s\n", 20, "value x", 16, "value h", 16, "outcome", 16,
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


     double slope = ((*f)(xph) -  (*f)(xmh)) / (2*dx) ;
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
