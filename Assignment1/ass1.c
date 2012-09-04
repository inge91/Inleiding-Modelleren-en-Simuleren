#include <stdio.h>
#include <math.h>

// colors are nice
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void compute_sum();

int main(void)
{
    
    // Unsigned char byte is the size of a byte?
    float f;
    printf("The size of a float: %d\n", sizeof(f));
    double d;
    printf("The size of a double: %d\n", sizeof(d));
    long double ld;
    printf("The size of a long double: %d\n", sizeof(ld));

    //Calculating the smalles possible precision between any two numbers
    float i = 1.0;
    //printf("%f\n", i/2.0);
    float j;

    // is only an approximation of the machine precision
    while( i != 0.0 ) {
        j = i;
        //printf("%f\n", j);
        i /= 2.0;
    }

    printf("Machine precision for floats: %f\n", j);
    d = 1.0;
    //printf("%f\n", i/2.0);
    double k;

    // is only an approximation of the machine precision
    while( d != 0.0 ){
        k = d;
        //printf("%f\n", j);
        d /= 2.0;
    }

    printf("Machine precision for doubles: %f\n" , k);
    ld = 1.0;
    //printf("%Lf\n", ld/2.0);
    long double l;
    // is only an approximation of the machine precision
    while( ld != 0.0 ){
        l = ld;
        ld /= 2.0;
    }
    printf("Machine precision for long doubles: %Lf\n", l);
    

    compute_sum();

    return 0;
}

// assignment 4
void compute_sum()
{
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
        f_sum_high += 1.0/i;
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
