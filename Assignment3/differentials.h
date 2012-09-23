#ifndef DIFFERENTIALS_H
#define DIFFERENTIALS_H

int Euler(double t0, double t1, double dt, double * y0, double * y1, int N,
          int f(double, double *, double *, void *), void * params);

#endif
