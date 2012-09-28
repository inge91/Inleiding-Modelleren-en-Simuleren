#ifndef DIFFERENTIALS_H
#define DIFFERENTIALS_H
typedef struct
{
    int N;
} param_struct;

int Euler(double t0, double t1, double dt, double * y0, double * y1, int N,
          int f(double, double *, double *, void *), void * params);

int RungeKutta2(double t0, double t1, double dt, double * y0, double * y1,
                int N, int f(double, double *, double *, void *), void * params);

int RungeKutta4(double t0, double t1, double dt, double * y0, double * y1,
                int N, int f(double, double *, double *, void *), void * params);

void add_array(double *dest, const double *source, double multiplyer, int N);
void divide_array(double *dest, const double *source, double x, int N);
void multiply_array(double *dest, const double *source, double x, int N);
void copy_array(double *dest, const double *source, int N);

#endif
