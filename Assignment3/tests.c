#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "differentials.h"

#define RED   "\x1b[31m"
#define RESET "\x1b[0m"

void print_error(char *method, double result, double expected);


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

int f4(double t, double *y, double *dy, void *params)
{
    for (int i = 0; i < ((param_struct *)params)->N; ++i)
    {
        dy[i] = y[i] * y[i];
    }

    return 0;
}


void test_functions()
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

    // f = y * y, with t0 starting at ‐1 and y0 at 1, integrating to t = 1 
    printf("\n");

    y0[0] = 1;
    outcome = -0.1;
    for(int i = 0; i < iter_size; i++) {
        printf("Experimentation with dt = %f\n", iter[i] );
        Euler(-1, 1, iter[i], y0, y1, 1, &f4, (void*) ps);
        print_error("Euler", y1[0], outcome);

        RungeKutta2(-1, 1, iter[i], y0, y1, 1, &f4, (void*) ps);
        print_error("RungeKutta2", y1[0], outcome);

        RungeKutta4(-1, 1, iter[i], y0, y1, 1, &f4, (void*) ps);
        print_error("RungeKutta4", y1[0], outcome);
    }

    printf("\n");

    // f = y * y, with t0 starting at 1 and y0 at -1, integrating to t = 10
    y0[0] = -1;
    outcome = -0.1;
    for(int i = 0; i < iter_size; i++) {
        printf("Experimentation with dt = %f\n", iter[i] );
        Euler(1, 10, iter[i], y0, y1, 1, &f4, (void*) ps);
        print_error("Euler", y1[0], outcome);

        RungeKutta2(1, 10, iter[i], y0, y1, 1, &f4, (void*) ps);
        print_error("RungeKutta2", y1[0], outcome);

        RungeKutta4(1, 10, iter[i], y0, y1, 1, &f4, (void*) ps);
        print_error("RungeKutta4", y1[0], outcome);
    }
}

void print_error(char *method, double result, double expected)
{
    printf("%-11s gives: %f\t\t" RED "(Error: %f)" RESET "\n", method, result,
           fabs(result - expected));
}


// ------------------------------------
// Coupled ODEs
// ------------------------------------
//

// ------------------------------------
// Harmonic Oscillator
// ------------------------------------

// the function used for the harmonic oscillator
int harmonic_oscillator(double k, double *y, double *dy, void *params)
{
    // y[0]  = s(k)
    // y[1]  = v(k)
    //
    // dy[0] = s'(k) = v(k)
    // dy[1] = v'(k) = -ks
    
    dy[0] = y[1];
    dy[1] = -k * y[0];

    return 0;
}

void test_oscillator()
{
    printf("\n");
    printf("===================\n");
    printf("Harmonic oscillator\n");
    printf("===================\n");
    double y0[2] = {1, 0};
    double y1[2];

    Euler(0, 10, 0.1, y0, y1, 2, &harmonic_oscillator, 0);
    printf("Euler, 10%% timesteps:\t\t\ts(t1) = %f, v(t1) = %f\n", y1[0], y1[1]);

    Euler(0, 10, 0.05, y0, y1, 2, &harmonic_oscillator, 0);
    printf("Euler, 5\%% timesteps:\t\t\ts(t1) = %f, v(t1) = %f\n", y1[0], y1[1]);

    printf("\n");

    RungeKutta2(0, 10, 0.1, y0, y1, 2, &harmonic_oscillator, 0);
    printf("RungeKutta2, 10\%% timesteps:\t\ts(t1) = %f, v(t1) = %f\n", y1[0], y1[1]);

    RungeKutta2(0, 10, 0.05, y0, y1, 2, &harmonic_oscillator, 0);
    printf("RungeKutta2, 5\%% timesteps:\t\ts(t1) = %f, v(t1) = %f\n", y1[0], y1[1]);

    printf("\n");

    RungeKutta4(0, 10, 0.1, y0, y1, 2, &harmonic_oscillator, 0);
    printf("RungeKutta4, 10\%% timesteps:\t\ts(t1) = %f, v(t1) = %f\n", y1[0], y1[1]);

    RungeKutta4(0, 10, 0.05, y0, y1, 2, &harmonic_oscillator, 0);
    printf("RungeKutta4, 5\%% timesteps:\t\ts(t1) = %f, v(t1) = %f\n", y1[0], y1[1]);

    RungeKutta4(0, 10, 0.005, y0, y1, 2, &harmonic_oscillator, 0);
    printf("RungeKutta4, 0.5\%% timesteps:\t\ts(t1) = %f, v(t1) = %f\n", y1[0], y1[1]);

    printf("\n");
    printf("Please enjoy these lovely plots.\n");
    RungeKutta4_plot(0, 20, 0.01, y0, y1, 2, &harmonic_oscillator, 0);
}

// ------------------------------------
// Lotka-Volterra
// ------------------------------------
//
// x' = -0.5x + 0.01xy
// y' = y - 0.1xy
// 
// Stable populations are found at:
// x = 0, y = 0
// x = 10, y = 50
int lotka_volterra(double t, double *y, double *dy, void *params)
{
    // y[0] = x(t)
    // y[1] = y(t)
    //
    // dy[0] = x'(t) = -0.5x(t) + 0.01x(t)y(t)
    // dy[1] = y'(t) = y(t) - 0.1x(t)y(t)

    dy[0] = -0.5 * y[0] + 0.01 * y[0] * y[1];
    dy[1] = y[1] - 0.1 * y[0] * y[1];

    return 0;
}

void test_lotka()
{
    printf("\n");
    printf("==============\n");
    printf("Lotka-Volterra\n");
    printf("==============\n");

    printf("Starting at the equilibrium with x0 = 10 and y0 = 50\n");
    double y0[2] = {10, 50};
    double y1[2];
    RungeKutta4_plot(0, 20, 0.005, y0, y1, 2, &lotka_volterra, 0);

    printf("Starting close to the equilibrium with x0 = 8 and y0 = 52\n");
    y0[0] = 8; y0[1] = 52;
    RungeKutta4_plot(0, 20, 0.005, y0, y1, 2, &lotka_volterra, 0);

    printf("Starting further from the equilibrium with x0 = 40 and y0 = 20\n");
    y0[0] = 40; y0[1] = 20;
    RungeKutta4_plot(0, 20, 0.005, y0, y1, 2, &lotka_volterra, 0);
}

// ------------------------------------
// Verhulst model
// ------------------------------------
//
// x' = -0.5x + 0.01xy
// y' = (1 - y/100)y - 0.1xy
int verhulst(double t, double *y, double *dy, void *params)
{
    // y[0] = x(t)
    // y[1] = y(t)
    //
    // dy[0] = x'(t) = -0.5x(t) + 0.01x(t)y(t)
    // dy[1] = y'(t) = (1 - y(t)/100)y(t) - 0.1x(t)y(t)

    dy[0] = -0.5 * y[0] + 0.01 * y[0] * y[1];
    dy[1] = (1 - y[1]/100.0) * y[1] - 0.1 * y[0] * y[1];

    return 0;
}

void test_verhulst()
{
    printf("\n");
    printf("========\n");
    printf("Verhulst\n");
    printf("========\n");

    printf("Starting at the previous equilibrium with x0 = 10 and y0 = 50\n");
    double y0[2] = {10, 50};
    double y1[2];
    RungeKutta4_plot(0, 20, 0.005, y0, y1, 2, &verhulst, 0);

    printf("Starting close to the previous equilibrium with x0 = 8 and y0 = 52\n");
    y0[0] = 8; y0[1] = 52;
    RungeKutta4_plot(0, 20, 0.005, y0, y1, 2, &verhulst, 0);

    printf("Starting further from the previous equilibrium with x0 = 40 and y0 = 20\n");
    y0[0] = 40; y0[1] = 20;
    RungeKutta4_plot(0, 20, 0.005, y0, y1, 2, &verhulst, 0);
}

// ------------------------------------
// Gilpin model
// ------------------------------------
//
// x' = x(1 - 0.001x - 0.001y - 0.01z)
// y' = y(1 - 0.001y - 0.0015x - 0.001z)
// z' = z(0.005x + 0.0005y - 1)
int gilpin(double t, double *y, double *dy, void *params)
{
    // y[0] = x(t)
    // y[1] = y(t)
    // y[2] = z(t)
    //
    // dy[0] = x'(t) = x(t) * (1 - 0.001x(t) - 0.001y(t) - 0.01z(t)
    // dy[1] = y'(t) = y(t) * (1 - 0.001y(t) - 0.0015x(t) - 0.001z(t)
    // dy[2] = z'(t) = z(t) * (0.005x(t) + 0.0005y(t) - 1)

    dy[0] = y[0] * (1 - 0.001*y[0] - 0.001*y[1] - 0.01*y[2]);
    dy[1] = y[1] * (1 - 0.001*y[1] - 0.0015*y[0] - 0.001*y[2]);
    dy[2] = y[2] * (0.005*y[0] + 0.0005*y[1] - 1);

    return 0;
}

void test_gilpin()
{
    printf("\n");
    printf("======\n");
    printf("Gilpin\n");
    printf("======\n");

    printf("Starting at x0 = 50, y0 = 50, and z0 = 50\n");
    double y0[3] = {50, 50, 50};
    double y1[3];
    RungeKutta4_plot(0, 50, 0.005, y0, y1, 3, &gilpin, 0);

    printf("Starting at x0 = 100, y0 = 100, and z0 = 500\n");
    y0[0] = 100; y0[1] = 100; y0[2] = 500;
    RungeKutta4_plot(0, 50, 0.005, y0, y1, 3, &gilpin, 0);
}

int main(int argc, char const *argv[])
{
    test_functions();
    test_oscillator();
    test_lotka();
    test_verhulst();
    test_gilpin();

    return 0;
}
