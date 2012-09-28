#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "differentials.h"

#define RED   "\x1b[31m"
#define RESET "\x1b[0m"

void print_error(char *method, double result, double expected);

typedef struct
{
    int N;
} param_struct;

int f(double t, double *y, double *dy, void *params)
{
    for (int i = 0; i < ((param_struct*)params)->N; i++) {
        dy[i] = 1;
    }

    return 0;
}


int f2(double t, double *y, double *dy, void *params)
{
    for (int i = 0; i < ((param_struct*)params)->N; i++) {
        dy[i] = t;
    }

    return 0;
}


int f3(double t, double *y, double *dy, void *params)
{
    for (int i = 0; i < ((param_struct*)params)->N; i++) {
        dy[i] = y[i];
    }

    return 0;
}



int main(int argc, const char *argv[])
{
    double y0[1] = {0};
    double y1[1];

    param_struct *ps = (param_struct *) malloc( sizeof(param_struct) );
    ps->N = 1;

    double outcome;

    outcome = 10;
    printf("Outcome should be 10\n");
    for (double i = 0.5; i <= 1.5 ; i += 0.5) {
        printf("Experimentation with dt = %f\n", i );
        Euler(0, 10, i, y0, y1, 1, &f, (void*) ps);
        print_error("Euler", y1[0], outcome);

        RungeKutta2(0, 10, i, y0, y1, 1, &f, (void*) ps);
        print_error("RungeKutta2", y1[0], outcome);

        RungeKutta4(0, 10, i, y0, y1, 1, &f, (void*) ps);
        print_error("RungeKutta4", y1[0], outcome);
    }

    printf("Experimentation with dt = %d\n", 10 );
    Euler(0, 10, 10, y0, y1, 1, &f, (void*) ps);
    print_error("Euler", y1[0], outcome);

    RungeKutta2(0, 10, 10, y0, y1, 1, &f, (void*) ps);
    print_error("RungeKutta2", y1[0], outcome);

    RungeKutta4(0, 10, 10, y0, y1, 1, &f, (void*) ps);
    print_error("RungeKutta4", y1[0], outcome);

    printf("\n");

    double iter[] = {0.05, 0.1, 0.5, 5};
    int iter_size = 4;

    outcome = 50;
    printf("Outcome should be 50\n");
    for (int i = 0; i < iter_size ; i++) {
        printf("Experimentation with dt = %f\n", iter[i] );
        Euler(0, 10, iter[i], y0, y1, 1, &f2, (void*) ps);
        print_error("Euler", y1[0], outcome);

        RungeKutta2(0, 10, iter[i], y0, y1, 1, &f2, (void*) ps);
        print_error("RungeKutta2", y1[0], outcome);

        RungeKutta4(0, 10, iter[i], y0, y1, 1, &f2, (void*) ps);
        print_error("RungeKutta4", y1[0], outcome);
    }

    printf("\n");

    outcome = 144;
    printf("Outcome should be approximately 144\n");
    // We now start at y0 = 1
    y0[0] =1;

    for (int i = 0; i < iter_size ; i++) {
        printf("Experimentation with dt = %f\n", iter[i] );
        Euler(0, 5, iter[i], y0, y1, 1, &f3, (void*) ps);
        print_error("Euler", y1[0], outcome);

        RungeKutta2(0, 5, iter[i], y0, y1, 1, &f3, (void*) ps);
        print_error("RungeKutta2", y1[0], outcome);

        RungeKutta4(0, 5, iter[i], y0, y1, 1, &f3, (void*) ps);
        print_error("RungeKutta4", y1[0], outcome);
    }
}

void print_error(char *method, double result, double expected)
{
    printf("%-11s gives: %f\t\t" RED "(Error: %f)" RESET "\n", method, result,
           fabs(result - expected));
}
