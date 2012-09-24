#include <stdlib.h>
#include <string.h>

#include "differentials.h"

/*
t0 – the start value t0 of t (input)
t1 – the final value of t (input)
dt – the increment in t (input)
y0[N] – the values of the functions y_n(t) at t0 (input)
y1[N] – the values of the functions y_n(t) at t1 (output)
N – the dimension of y
int f(double t, double * y, double * dy, void * params) – computes
the vector of derivatives dy[N] of y[N], given t, y[N] and params
void * params – a pointer to a struct containing any parameters needed
by f (input)
All three functions return an estimate of y(t1) in y1.
All functions return 0 upon success, or -1 when a computational error
occurs (overflow, NaN or such)
*/
int Euler(double t0, double t1, double dt, double * y0, double * y1, int N,
          int f(double, double *, double *, void *), void * params)
{
    // save the values for y at the previous t
    double yt_previous[N];

    for (int i = 0; i < N; i++) {
        yt_previous[i] = y0[i];
    }

    // start at t0 + dt, since the values at t0 are already known
    for (int t = t0 + dt; t <= t1; t += dt) {
        // make arrays for the values of y at t, and the derivatives of y at t-1
        double yt[N];
        double yt_prev_deriv[N];
        
        (*f)(t, yt_previous, yt_prev_deriv, params);

        // getting the new values for yt
        for (int i = 0; i < N; i++) {
            yt[i] = yt_previous[i] + (dt * yt_prev_deriv[i]);
        }

        for (int i = 0; i < N; i++) {
            yt_previous[i] = yt[i];
        }
    }

    for (int i = 0; i < N; i++) {
        y1[i] = yt_previous[i];
    }

    return 0;
}

int RungeKutta2(double t0, double t1, double dt, double * y0, double * y1,
                int N, int f(double, double *, double *, void *), void * params)
{
    // because the loop starts at y_n+1, use the values of y0 as initial values
    // for y_n
    double yt[N];
    for (int i = 0; i < N; i++) {
        yt[i] = y0[i];
    }

    // iterate from t0 to t1 in steps of dt
    for (int t = t0 + dt; t <= t1; ++t) {
        // yn+1 = yn + 1/6 (k1 + 2k2 + 2k3 + k4)
        double yt_deriv[N];

        // k1 = dt * f(tn, yn)
        double k1[N];
        (*f)(t, yt, yt_deriv, params);

        multiply_array(k1, yt_deriv, dt, N);

        // k2 = dt * f(tn + 0.5dt, yn + 0.5k1)
        double k2[N], yt_midway[N], yt_midway_deriv[N];
        copy_array(yt_midway, yt, N);
        add_array(yt_midway, k1, 0.5, N);
        (*f)(t + (0.5*dt), yt_midway, yt_midway_deriv, params);

        multiply_array(k2, yt_midway_deriv, dt, N);

        // copy the values back to yt for the next iteration
        for (int i = 0; i < N; ++i) {
            yt[i] += (0.5 * k1[i]) + (0.5 * k2[i]);
        }
    }

    // copy yt to y1
    copy_array(y1, yt, N);

    return 0;
}

int RungeKutta4(double t0, double t1, double dt, double * y0, double * y1,
                int N, int f(double, double *, double *, void *), void * params)
{
    // because the loop starts at y_n+1, use the values of y0 as initial values
    // for y_n
    double yt[N];
    for (int i = 0; i < N; i++) {
        yt[i] = y0[i];
    }

    // iterate from t0 to t1 in steps of dt
    for (int t = t0 + dt; t <= t1; ++t) {
        // yn+1 = yn + 1/6 (k1 + 2k2 + 2k3 + k4)
        double yt_deriv[N];

        // k1 = dt * f(tn, yn)
        double k1[N];
        (*f)(t, yt, yt_deriv, params);

        multiply_array(k1, yt_deriv, dt, N);

        // k2 = dt * f(tn + 0.5dt, yn + 0.5k1)
        double k2[N], yt_midway[N], yt_midway_deriv[N];
        copy_array(yt_midway, yt, N);
        add_array(yt_midway, k1, 0.5, N);
        (*f)(t + (0.5*dt), yt_midway, yt_midway_deriv, params);

        multiply_array(k2, yt_midway_deriv, dt, N);

        // k3 = dt * f(tn + 0.5dt, yn + 0.5k2)
        double k3[N];
        copy_array(yt_midway, yt, N);
        add_array(yt_midway, k3, 0.5, N);
        (*f)(t + (0.5*dt), yt_midway, yt_midway_deriv, params);

        multiply_array(k3, yt_midway_deriv, dt, N);

        // k4 = dt * f(tn + dt, yn + k3)
        double k4[N], yt_fullstep[N], yt_fullstep_deriv[N];
        copy_array(yt_fullstep, yt, N);
        add_array(yt_fullstep, k3, 1, N);
        (*f)(t + dt, yt_fullstep, yt_fullstep_deriv, params);

        multiply_array(k4, yt_fullstep_deriv, dt, N);

        // copy the values back to yt for the next iteration
        for (int i = 0; i < N; ++i) {
            // yn+1 = yn + 1/6 (k1 + 2k2 + 2k3 + k4)
            yt[i] += (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]) / 6;
        }
    }

    // copy yt to y1
    copy_array(y1, yt, N);

    return 0;
}

// Add the values of the source array, multiplied by the multiplyer, to the dest
// array. N holds the size of the arrays.
void add_array(double *dest, double *source, double multiplyer, int N)
{
    for (int i = 0; i < N; ++i)
    {
        dest[i] = source[i] * multiplyer;
    }
}

// Divide each element of the source array by x.
// N holds the size of the array
void divide_array(double *dest, double *source, double x, int N)
{
    for (int i = 0; i < N; ++i) {
        dest[i] = source[i] / x;
    }
}

// Multiply each element of the source array by x.
// N holds the size of the array
void multiply_array(double *dest, double *source, double x, int N)
{
    for (int i = 0; i < N; ++i) {
        dest[i] = source[i] * x;
    }
}

void copy_array(double *dest, double *source, int N)
{
    for (int i = 0; i < N; ++i) {
        dest[i] = source[i];
    }
}
