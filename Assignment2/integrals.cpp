#include <iostream>
#include <stdio.h>

double rectangle_rule(double interval_min, double interval_max,int subsection_amount,
               double (*f)(double));
double first_int(double);
double trapezoidal_rule(double interval_min, double interval_max,
                        int subsection_amount, double(*f)(double));
//double simpsons_rule(double interval_min, double interval_max,
  //            int subsection_amount, double (*f)(double));
double two_point_gauss(double interval_min, double interval_max,
                int subsection_amount, double (*f)(double));

int main(){
    double result = trapezoidal_rule(0, 1, 999, first_int);
    printf("%f", result);
}


// Integration using the rectangle rule with topleft corner approcimation
double rectangle_rule(double interval_min, double interval_max,
                      int subsection_amount, double (*f)(double))
{
    double interval_size = (interval_max - interval_min) / subsection_amount;


    double add;
    add = 0;
    for(int i = 1; i < subsection_amount; i++) {
        add += f(interval_min + (i * interval_size));
    }
    return interval_size * add;

}


// Integration using the trapezoidal rule (uniform grid is assumed)
// FIXME
double trapezoidal_rule(double interval_min, double interval_max,
                        int subsection_amount, double(*f)(double))
{
    double interval_size = (interval_max - interval_min) / subsection_amount;
    std::cout<<"interval size"<<std::endl;
    std::cout<<interval_size<<std::endl;

    double add;
    double rectangle_size;
    double triangle_size;
    add = 0;


    for(int i = 0; i < subsection_amount - 1; i++) {
        // Calculate function values a and b
        double a = f(interval_min + (i * interval_size));
        double b = f(interval_min + ((i+1) * interval_size));
        // Calculating triangle size
        rectangle_size = a * interval_size;


        triangle_size = ((b - a) * interval_size)/2;

        add += rectangle_size + triangle_size;
    }



    return add;

}

// Using simson
double simpsons_rule(double interval_min, double interval_max,
              int subsection_amount, double (*f)(double)){

    double add;

    for(int i = 0; i < subsection_amount; i ++)
    {

    }


}

double two_point_gauss(double interval_min, double interval_max,
                int subsection_amount, double (*f)(double))
{

}

//All integrals are given as functions
double first_int(double x)
{
    return x*x;
}


