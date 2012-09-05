#include <stdio.h>
#include <math.h>
#include <float.h>

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
float kahan_summation(int lower_bound, int upper_bound);

int main(void)
{
    
    ass1();
    compute_sum();

    return 0;
}

// assignment 1
void ass1() 
{
    printf(ANSI_COLOR_RED "Exercise 1\n" ANSI_COLOR_RESET);

    // determining size in bytes of the datatypes
    float f;
    printf("The size of a float: %d bytes\n", sizeof(f));
    double d;
    printf("The size of a double: %d bytes\n", sizeof(d));
    long double ld;
    printf("The size of a long double: %d bytes\n", sizeof(ld));

    printf("\n\n");
    // machine precision case of the float
    f = 1.0;
    float j;

    // look for smallest f that makes f + 1 > 1
    while( (f + 1) != 1.0) {
        j = f;
        f /= 2.0;
    }

    printf("Machine precision for floats: %G\n", j);
    printf("Float.h machine precision for floats: %G\n", FLT_EPSILON);
    printf("\n");
    
    // machine precision case of the double 
    d = 1.0 ;
    double k;

    while( (d + 1) != 1.0) {
        k = d;
        d /= 2.0;
    }

    printf("Machine precision for doubles: %G\n" , k);
    printf ("Float.h machine precision for doubles: %G\n", DBL_EPSILON);
    printf("\n");

    // machine precision case of the long double
    ld = 1.0;
    long double l;

    while((ld + 1.0) != 1.0) {
        l = ld;
        ld /= 2.0;
    }

    printf("Machine precision for long doubles: %LG\n", l);
    printf("Machine precision for long doubles: %LG\n", LDBL_EPSILON);
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
