#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <vector>

#include "integrals.h"
// Integration using the rectangle rule with topleft corner approximation
double rectangle_rule(double interval_min, double interval_max,
                      int subsection_amount, double (*f)(double))
{
    double interval_size = (interval_max - interval_min) / subsection_amount;


    double add;
    add = 0;
    for(int i = 0; i < subsection_amount; i++) {
        add += f(interval_min + (i * interval_size));
    }
    return interval_size * add;

}

// Integrating using the rectangle rule with midpoint rule
double midpoint_rule(double a, double b, double (*f)(double))
{

    return (b-a) * f((a + b) / 2);


}


// Integration using the trapezoidal rule (uniform grid is assumed)
double trapezoidal_rule(double interval_min, double interval_max,
                        int subsection_amount, double(*f)(double))
{
    double interval_size = (interval_max - interval_min) / subsection_amount;

    double add;
    double rectangle_size;
    double triangle_size;
    add = 0;


    for(int i = 0; i < subsection_amount; i++) {
        // Calculate function values a and b
        double a_y = f(interval_min + (i * interval_size));
        double b_y = f(interval_min + ((i+1) * interval_size));
        
	// Calculating rectangle size
        rectangle_size = a_y * interval_size;

	// Calculat triangle size
        triangle_size = ((b_y - a_y) * interval_size)/2;

        add += rectangle_size + triangle_size;
    }

    return add;

}

// Using simpsons rule
double simpsons_rule(double interval_min, double interval_max,
              int subsection_amount, double (*f)(double)){

    double add, rect, trap, n, np1;
    double interval_size = (interval_max - interval_min) / subsection_amount;

    for(int i = 0; i < subsection_amount - 1; i ++)
    {
         n = ( interval_min + (i * interval_size));
         np1 = ( interval_min + ((i+1) * interval_size));

        rect = midpoint_rule(n, np1, f);

        trap = trapezoidal_rule(n, np1, 1, f);

        add += ((2 * rect) + trap) / 3;

    }

    return add;


}

// T
double two_point_gauss(double interval_min, double interval_max,
                int subsection_amount, double (*f)(double))
{
    double interval_size = (1 - (-1)) / subsection_amount;
    double quadrature;
    double min_max_diff = interval_max - interval_min,
           min_max_sum = interval_max + interval_min;

    // the function needs to be shifted to a [-1, 1] interval
    for (int i = 0; i < subsection_amount; i++) {
        double x0 = -1 + (i * interval_size);
        double x1 = -1 + ((i+1) * interval_size);

        double  sample_1 = x0 + 0.5 * interval_size * (1 + 1/sqrt(3));
        double  sample_2 = x0 + 0.5 * interval_size * (1 - 1/sqrt(3));

        quadrature += (*f)(0.5 * min_max_diff * sample_1 + 0.5 * min_max_sum);
        quadrature += (*f)(0.5 * min_max_diff * sample_2 + 0.5 * min_max_sum);
    }

    // when multiplying by 0.5, the answer is off by a factor 2
    // thus, multiply by 0.25!
    return 0.25 * min_max_diff * quadrature;
}

void ass4(){
    
    std::cout<< "Starting the accuracy test for numerical integration"<<std::endl;

    // Vector that contains all functions
    std::vector<fptr> function_vector;
    function_vector.push_back(int1);
    function_vector.push_back(int2);
    function_vector.push_back(int3);
    function_vector.push_back(int4);
    function_vector.push_back(int5);
    function_vector.push_back(int6);
    function_vector.push_back(int7);
    function_vector.push_back(int8);

    double answers[] = {1/3.0, 1/4.0, 1/5.0, 1/6.0, (M_E - 1.0) / M_E, 1 - (3.0/ (M_E * M_E)), 1-(21.0/  pow(M_E,20)), 2.82834};

    int interval[][2] = {{0,1}, {0,1}, {0,1}, {0,1}, {0,1}, {0,2}, {0,20}, {0,2}};

    int intervals = 2;

    for(int i = 0; i < function_vector.size(); i++)
    {
        printf("Found the solution to integral problem #%d with the ", i+1);

        while(intervals < 99999)
        {

            if((std::abs(answers[i] - rectangle_rule(interval[i][0],interval[i][1], intervals, function_vector.at(i)))) < 0.0001)
                 {
                     printf("rectangle rule, using %d intervals\n", intervals);
                     printf("outcome: %f\n\n", rectangle_rule(interval[i][0],interval[i][1], intervals, function_vector.at(i)));
                     intervals = 2;
                     break;
                 }
                 else if((std::abs(answers[i] - trapezoidal_rule(interval[i][0],interval[i][1], intervals, function_vector.at(i)))) < 0.0001)
                 {                
                     printf("trapezoidal rule, using %d intervals\n", intervals);
                     printf("outcome: %f\n\n", trapezoidal_rule(interval[i][0],interval[i][1], intervals, function_vector.at(i)));
                     intervals = 2;
                     break;
                 }
                 else if((std::abs(answers[i] - simpsons_rule(interval[i][0],interval[i][1], intervals, function_vector.at(i)))) < 0.0001)
                 {
                     printf("Simpsons rule, using %d intervals\n", intervals);
                     printf("outcome: %f\n\n", simpsons_rule(interval[i][0],interval[i][1], intervals, function_vector.at(i)));
                     intervals = 2;
                     break;
                 }
                 else if((std::abs(answers[i]) - two_point_gauss(interval[i][0],interval[i][1], intervals, function_vector.at(i))) < 0.0001)
                 {
                     printf("two-point Gauss rule, using %d intervals\n", intervals);
                     printf("outcome: %f\n\n", two_point_gauss(interval[i][0],interval[i][1], intervals, function_vector.at(i)));
                     intervals = 2;
                     break;
                 }

                // Not yet right answer found, multiplying the amount of intervals
                 intervals *= 2;
        }

        if(intervals > 99999)
        {
            printf(" ERROR: A good approximation could not be found\n\n");
            intervals = 2;

        }



    }

    std::cout << std::endl;
}

//All integrals are given as functions
double int1(double x)
{
    return x*x;
}

double int2(double x)
{
    return x*x*x;
}

double int3(double x)
{
    return x*x*x*x;
}

double int4(double x)
{
    return x*x*x*x*x;
}


double int5(double x)
{
    return pow(M_E,-x);
}

double int6(double x)
{
    return x* pow(M_E,-x);
}

double int7(double x)
{
    return  x*pow(M_E,-x);
}

double int8(double x)
{
    return pow(x, -0.5);
}





