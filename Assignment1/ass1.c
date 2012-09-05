#include <stdio.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include <string.h>

#include "ranges.h"

// colors are nice
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void compute_sum();
void ass1();
void ass2();
float kahan_summation(int lower_bound, int upper_bound);
void ass3();
void speedtest();
void power();
void addition();
void substraction();
void multiplication();
void division();
void squareroot();

int main(void)
{
    
    ass1();
    ass2();
    speedtest();
    compute_sum(); // ass4

    return 0;
}

// assignment 1
void ass1() 
{
    printf(ANSI_COLOR_RED "Exercise 1\n" ANSI_COLOR_RESET);

    // determining size in bytes of the datatypes
    float f;
    printf("The size of a float:\t\t\t%d bytes\n", sizeof(f));
    double d;
    printf("The size of a double:\t\t\t%d bytes\n", sizeof(d));
    long double ld;
    printf("The size of a long double:\t\t%d bytes\n", sizeof(ld));

    printf("\n\n");
    // machine precision case of the float
    f = 1.0;
    float j;

    // look for smallest f that makes f + 1 > 1
    while( (f + 1) != 1.0) {
        j = f;
        f /= 2.0;
    }

    printf("Machine precision for floats:\t\t%G\n", j);
    printf("Float.h machine precision for floats:\t%G\n", FLT_EPSILON);
    printf("\n");
    
    // machine precision case of the double 
    d = 1.0 ;
    double k;

    while( (d + 1) != 1.0) {
        k = d;
        d /= 2.0;
    }

    printf("Machine precision for doubles:\t\t%G\n" , k);
    printf ("Float.h machine precision for doubles:\t%G\n", DBL_EPSILON);
    printf("\n");

    // machine precision case of the long double
    ld = 1.0;
    long double l;

    while((ld + 1.0) != 1.0) {
        l = ld;
        ld /= 2.0;
    }

    printf("Machine precision for long doubles:\t%LG\n", l);
    printf("Machine precision for long doubles:\t%LG\n", LDBL_EPSILON);
    printf("\n\n");

    print_ranges();
    printf("\n");
}   

// assignment 2 
void ass2(){
    
    printf(ANSI_COLOR_RED "Exercise 2\n" ANSI_COLOR_RESET);

    // Some experimentations 
    printf("The different operations we tried and their outcome:\n\n");
    printf("Division of 1.0 by zero:\t\t\t\t%f\n", 1.0f/0.0f);
    printf("Division of -1.0 by zero:\t\t\t\t%f\n", -1.0f/0.0f);
    printf("Division of 0.0 by 0.0:\t\t\t\t\t%f\n", 0.0/0.0);
    printf("Overflowing a float by making it too big:\t\t%f\n", pow(10.0f,100000000000.0f));
    printf("Overflowing a float by making it too small:\t\t%f\n", pow(-10.0f,100000000000.0f));
    printf("Infinity - infinity :\t\t\t\t\t%f\n",  pow(10.0f,100000000000.0f) - pow(10.0f,100000000000.0f));
    printf("Square root of -1:\t\t\t\t\t%f\n", sqrt(-1));
    printf("Underflowing a float by creating a too small number:\t%f\n",pow(10, -10000000000));
    printf("\n");
}


// assignment 3
void addition()
{
    
    float k = 100;
    double j;
    clock_t begin_time, end_time;
    double  time_taken2, time_taken3;

    begin_time = clock();

    // 1000 power operations
    for(int i = 0; i < 9999999; i ++) {
        j = k + k;

    }
    end_time = clock();
    
    time_taken2 = (end_time - begin_time) / (double) CLOCKS_PER_SEC;

    printf("Elapsed time after 100,000 addition operations: %f seconds \n", time_taken2);

    begin_time = clock();

    // some loop unrolling
    for(int i = 0; i < 999999; i ++) {
        j = k + k;
        j = k + k;
        j = k + k;
        j = k + k;
        j = k + k;
        j = k + k;
        j = k + k;
        j = k + k;
        j = k + k;
        j = k + k;
    }
    end_time = clock();

    time_taken3 = (double)(end_time - begin_time) / (double) CLOCKS_PER_SEC;
    printf("Elapsed time of 1,000,000 addition operations that uses loop unrolling: %G seconds \n", time_taken3);

    printf("The mean of these 1,000,000 "
           "operations is %g ms\n", time_taken3 / 1000000.0 * 1000);

}

void substraction()
{
    float k = 100;

    double j;

    clock_t begin_time, end_time;
    double  time_taken2, time_taken3;

    begin_time = clock();

    // 1000 power operations
    for(int i = 0; i < 999999; i ++) {
        j = k - i;

    }
    end_time = clock();
    
    time_taken2 = (end_time - begin_time) / (double) CLOCKS_PER_SEC;

    printf("Elapsed time of 1,000,000 substraction operations: %f seconds \n", time_taken2);

    begin_time = clock();

    // some loop unrolling
    for(int i = 0; i < 99999; i ++) {
        j = 50 -100; 
        j = 18 - 17; 
        j = 1423 - 1346; 
        j = 1346 - 3145; 
        j = 6345 - 1345; 
        j = 34 - 12; 
        j = 3234 - 45; 
        j = 64 - 135; 
        j = 3456 - 345; 
        j = 63 - 3879; 
    }
    end_time = clock();

    time_taken3 = (double)(end_time - begin_time) / (double) CLOCKS_PER_SEC;
    printf("Elapsed time of 1,000,000 substraction operations that use loop unrolling: %f seconds \n", time_taken3);

    printf("The mean of these 1,000,000 "
           "operations is %g ms\n", time_taken3 / 1000000.0 * 1000);


}

void multiplication()
{
    
    float k = 100;

    double j;

    clock_t begin_time, end_time;
    double  time_taken2, time_taken3;

    begin_time = clock();

    // 1000 power operations
    for(int i = 0; i < 999999; i ++) {
        j = k * i;

    }
    end_time = clock();
    
    time_taken2 = (end_time - begin_time) / (double) CLOCKS_PER_SEC;

    printf("Elapsed time of 1,000,000 multiplication operations: %f seconds \n", time_taken2);

    begin_time = clock();

    // some loop unrolling
    for(int i = 0; i < 99999; i ++) {
        j = 50 *100; 
        j = 18 * 17; 
        j = 1423 * 1346; 
        j = 1346 * 3145; 
        j = 6345 * 1345; 
        j = 34 * 12; 
        j = 3234 * 45; 
        j = 64 * 135; 
        j = 3456 * 345; 
        j = 63 * 3879; 
    }
    end_time = clock();

    time_taken3 = (double)(end_time - begin_time) / (double) CLOCKS_PER_SEC;
    printf("Elapsed time of 1,000,000 multiplication operations that use loop unrolling: %f seconds \n", time_taken3);

    printf("The mean of these 1,000,000 "
           "operations is %g ms\n", time_taken3 / 1000000.0 * 1000);


}

void division()
{
    
    float k = 100;
    double j;

    clock_t begin_time, end_time;
    double  time_taken2, time_taken3;

    begin_time = clock();

    // 1000 power operations
    for(int i = 0; i < 999999; i ++) {
        j = k / (i+1);

    }
    end_time = clock();
    
    time_taken2 = (end_time - begin_time) / (double) CLOCKS_PER_SEC;

    printf("Elapsed time of 1,000,000 division operations: %f seconds \n", time_taken2);

    begin_time = clock();

    // some loop unrolling
    for(int i = 0; i < 99999; i ++) {
        j = 50 /100; 
        j = 18 / 17; 
        j = 1423 / 1346; 
        j = 1346 / 3145; 
        j = 6345 / 1345; 
        j = 34 / 12; 
        j = 3234 / 45; 
        j = 64 / 135; 
        j = 3456 / 345; 
        j = 63 / 3879; 
    }
    end_time = clock();

    time_taken3 = (double)(end_time - begin_time) / (double) CLOCKS_PER_SEC;
    printf("Elapsed time of 1,000,000 division operations that uses loop unrolling: %G seconds \n", time_taken3);

    printf("The mean of these 1,000,000 "
           "operations is %G ms\n", time_taken3 / 1000000.0 * 1000);

}


void power()
{
    float k = 100;
    double j;

    clock_t begin_time, end_time;
    double  time_taken2, time_taken3;

    begin_time = clock();

    // 1000 power operations
    for(int i = 0; i < 999999; i ++) {
        j = pow(i, k);

    }
    end_time = clock();
    
    time_taken2 = (end_time - begin_time) / (double) CLOCKS_PER_SEC;

    printf("Elapsed time of 1,000,000 power operations: %f seconds \n", time_taken2);

    begin_time = clock();

    // some loop unrolling
    for(int i = 0; i < 999999; i += 10) {
        j = pow(i, -1);
        j = pow(i, 1);
        j = pow(i, 2);
        j = pow(i, 3);
        j = pow(i, 4);
        j = pow(i, 5);
        j = pow(i, 6);
        j = pow(i, 7);
        j = pow(i, 8);
        j = pow(i, 9);
    }
    end_time = clock();

    time_taken3 = (double)(end_time - begin_time) / (double) CLOCKS_PER_SEC;
    printf("Elapsed time of 1,000,000 power operations that uses loop unrolling: %f seconds \n", time_taken3);

    printf("The mean of these 1,000,000 "
           "operations is %g ms\n",time_taken3 / 1000000.0 * 1000);


}

void squareroot(){

    float k = 100;

    double j;

    clock_t begin_time, end_time;
    double  time_taken2, time_taken3;

    begin_time = clock();

    // 1000 power operations
    for(int i = 0; i < 999999; i ++) {
        j = sqrt(i);

    }
    end_time = clock();
    
    time_taken2 = (end_time - begin_time) / (double) CLOCKS_PER_SEC;

    printf("Elapsed time of 1,000,000 pow operations: %f seconds \n", time_taken2);

    begin_time = clock();

    // some loop unrolling
    for(int i = 0; i < 999999; i += 10) {
        j = sqrt(i);
        j = sqrt(i + 1);
        j = sqrt(i + 2);
        j = sqrt(i + 3);
        j = sqrt(i + 4);
        j = sqrt(i + 5);
        j = sqrt(i + 6);
        j = sqrt(i + 7);
        j = sqrt(i + 8);
        j = sqrt(i + 9);
    }
    end_time = clock();

    time_taken3 = (double)(end_time - begin_time) / (double) CLOCKS_PER_SEC;
    printf("Elapsed time of 1,000,000 pow operations that use loop unrolling: %f seconds \n", time_taken3);

    printf("The mean of these 1,000,000 "
           "operations is %g ms\n",time_taken3 / 10000000.0 * 1000);


}


void speedtest(){
    printf(ANSI_COLOR_RED "Exercise 3\n" ANSI_COLOR_RESET);
    addition();
    printf("\n");
    substraction();
    printf("\n");
    division();
    printf("\n");
    multiplication();
    printf("\n");
    power();
    printf("\n");
    squareroot();
    printf("\n");
}




// assignment 4
void compute_sum()
{

    printf(ANSI_COLOR_RED "Exercise 4\n" ANSI_COLOR_RESET);
    int low_N = pow(10, 8);
    int high_N = 2 * pow(10, 8);

    float f_sum_low = 0, f_sum_high = 0;
    double d_sum_low = 0, d_sum_high = 0;

    // low N with floats forwards
    for (int i = 1; i < low_N; ++i) {
        f_sum_low += 1.0/i;
    }

    // high N with floats forwards
    for (int i = 1; i < high_N; ++i) {
        f_sum_high += 1.0/i;
    }

    printf("\n");
    printf(ANSI_COLOR_GREEN "Floats:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "Forwards:\n" ANSI_COLOR_RESET);
    printf("Sum of 1/i for i from 1 to 10^8:\t\t%f\n", f_sum_low);
    printf("Sum of 1/i for i from 1 to 2 * 10^8:\t\t%f\n", f_sum_high);

    f_sum_high = 0; f_sum_low = 0;

    // low N with floats backwards
    for (int i = low_N; i > 0; --i) {
        f_sum_low += 1.0/i;
    }
    
    // high N with floats backwards
    for (int i = high_N; i > 0; --i) {
        f_sum_high += 1.0/i;
    }

    printf("\n");
    printf(ANSI_COLOR_CYAN "Backwards:\n" ANSI_COLOR_RESET);
    printf("Sum of 1/i for i from 1 to 10^8:\t\t%f\n", f_sum_low);
    printf("Sum of 1/i for i from 1 to 2 * 10^8:\t\t%f\n", f_sum_high);

    // low N with doubles
    for (int i = 1; i < low_N; ++i) {
        d_sum_low += 1.0/i;
    }

    // high N with doubles
    for (int i = 1; i < high_N; ++i) {
        d_sum_high += 1.0/i;
    }

    printf("Sum with floats using Kahan summation:\t\t%f", kahan_summation(1, low_N));

    printf("\n");

    printf("\n");
    printf(ANSI_COLOR_GREEN "Doubles:\n" ANSI_COLOR_RESET);
    printf(ANSI_COLOR_CYAN "Forwards:\n" ANSI_COLOR_RESET);
    printf("Sum of 1/i for i from 1 to 10^8:\t\t%f\n", d_sum_low);
    printf("Sum of 1/i for i from 1 to 2 * 10^8:\t\t%f\n", d_sum_high);

    d_sum_high = 0; d_sum_low = 0;

    // low N with doubles backwards
    for (int i = low_N; i > 0; --i) {
        d_sum_low += 1.0/i;
    }
    
    // high N with doubles backwards
    for (int i = high_N; i > 0; --i) {
        d_sum_high += 1.0/i;
    }

    printf("\n");
    printf(ANSI_COLOR_CYAN "Backwards:\n" ANSI_COLOR_RESET);
    printf("Sum of 1/i for i from 1 to 10^8:\t\t%f\n", d_sum_low);
    printf("Sum of 1/i for i from 1 to 2 * 10^8:\t\t%f\n", d_sum_high);
}

// sums a range of numbers' reciprocals using Kahan summation
float kahan_summation(int lower_bound, int upper_bound)
{
    float sum= 0;
    float c = 0;

    for (int i = lower_bound; i < upper_bound; ++i) {
        float j = 1.0/i;
        float y = j - c;
        float t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }

    return sum;
}
