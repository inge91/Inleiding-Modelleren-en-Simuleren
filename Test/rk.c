/*
 
    Assume y(t) = exp(-2*t) then y(0) = 1.0 and dy/dt = -2*y(t) so we can use following
    FIRST-ORDER ODE for testing:
 
           dy/dt = exp(-2*t) - 3*y(t)
            y(0) = 1.0
 
*/
 
 
#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#define dist  0.01        /* stepsize in t*/
#define MAX   5.0          /* max for t */
 
FILE *output;              /* internal filename */
 
void runge4(double t, double dt, double y[] , int N, double f(double, double *) );   /* Runge-Kutta function */
double f4(double t, double y[]);            /* function for derivatives */
 
void main()
{
  int N =1;
  double t, y[N];
 
 
  y[0]= 1.0;                                      /* initial position */
 
 
  for (t = 0.0; t<=MAX ; t += dist)                     /* time loop */
     {
       runge4(t,  dist, y, N, f4);
     }
 
}
void runge4(double t, double dt, double y[], int N, double f(double, double *) )
{
  double h=dt/2.0,            /* the midpoint */
  t1[N], t2[N], t3[N],          /* temporary storage arrays */
  k1[N], k2[N], k3[N],k4[N];    /* for Runge-Kutta */
  int i;
  
  for(i=0;i<N;i++) 
  {
      k1[i]=dt*f(t, y);
  }
  for(i=0;i<N;i++) 
  {
    t1[i]=y[i]+0.5*k1[i];
  }

  for (i=0;i<N;i++) 
  {
    k2[i]=dt*f(t+(dt * 0.5), t1);
  }
  
  for (i=0;i<N;i++) 
  {
  t2[i]=y[i]+0.5*(k2[i]);
  }

  for (i=0;i<N;i++) {
    k3[i]=dt*f(t + (dt * 0.5), t2);
  }
  
  for (i=0;i<N;i++) {
    t3[i]=y[i]+ (k3[i]);
  }
  for (i=0;i<N;i++) 
  {
    k4[i]= dt*f(t + dt, t3);
  }
 
  for (i=0;i<N;i++) 
  {
      y[i]+=(k1[i]+2*k2[i]+2*k3[i]+k4[i])/6.0;
  }
  printf("%f\n",y[0]);
}
 
double f4(double t, double y[])
{
  return(y[0]);     /* derivative of first equation */
}
