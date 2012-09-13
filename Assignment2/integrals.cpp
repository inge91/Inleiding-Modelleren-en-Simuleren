#define _USE_MATH_DEFINES // for C++
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <vector>

typedef double (*fptr)(double);

double rectangle_rule(double interval_min, double interval_max,int subsection_amount,
               double (*f)(double));
double int1(double);
double int2(double);
double int3(double);
double int4(double);
double int5(double);
double int6(double);
double int7(double);
double int8(double);
void ass4();

double trapezoidal_rule(double interval_min, double interval_max,
                        int subsection_amount, double(*f)(double));
double simpsons_rule(double interval_min, double interval_max,
            int subsection_amount, double (*f)(double));
double two_point_gauss(double interval_min, double interval_max,
                int subsection_amount, double (*f)(double));

// Integration using the rectangle rule with topleft corner approcimation
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

        rect = rectangle_rule(n, np1, 1, f);

        trap = trapezoidal_rule(n, np1, 1, f);

        add += ((2 * rect) + trap) / 3;

    }

    return add;


}

// T
double two_point_gauss(double interval_min, double interval_max,
                int subsection_amount, double (*f)(double))
{

    return 0;

}

int main(){
    std::cout<<trapezoidal_rule(0,1,8, int1)<<std::endl;
    std::cout<<simpsons_rule(0,1,8, int1)<<std::endl;
    //ass4();
    return 0;
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

        while(1)
        {

            if((std::abs(answers[i] - rectangle_rule(interval[i][0],interval[i][1], intervals, function_vector.at(i)))) < 0.01)
                 {
                     printf("rectangle rule, using %d intervals\n", intervals);
                     intervals = 2;
                     break;
                 }
                 else if((std::abs(answers[i] - trapezoidal_rule(interval[i][0],interval[i][1], intervals, function_vector.at(i)))) < 0.01)
                 {
                std::cout<< std::abs(answers[i]) - trapezoidal_rule(interval[i][0],interval[i][1], intervals, function_vector.at(i));
                     printf("trapezoidal rule, using %d intervals\n", intervals);
                     intervals = 2;
                     break;
                 }
                 else if((std::abs(answers[i] - simpsons_rule(interval[i][0],interval[i][1], intervals, function_vector.at(i)))) < 0.01)
                 {
                     printf("Simpsons rule, using %d intervals\n", intervals);
                     intervals = 2;
                     break;
                 }
                 else if((std::abs(answers[i]) - two_point_gauss(interval[i][0],interval[i][1], intervals, function_vector.at(i))) < 0.01)
                 {
                     printf("two-point Gauss rule, using %d intervals\n", intervals);
                     intervals = 2;
                     break;
                 }

                // Not yet right answer found, multiplying the amount of intervals
                 intervals *= 2;
        }



    }

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





