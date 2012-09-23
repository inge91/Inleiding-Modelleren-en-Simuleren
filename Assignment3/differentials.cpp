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
    double yt_previous[N];

    for (int i = 0; i < N; i++) {
        yt_previous[i] = y0[i];
    }

    for (int t = t0 + dt; t <= t1; t += dt) {
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
