#include <stdio.h>
#include <math.h>
#include <stdlib.h> 

FILE *output;              /* internal filename */

typedef struct
{
    int N;
} param_struct;

void runge4(double t0, double t1, double dt, double y0[], double y1[], int N, int f(double, double *, double*, void *), void *params );   /* Runge-Kutta function */
double f4(double t, double y[]);            /* function for derivatives */
int f42(double t, double * y, double * dy, void *);

void main()
{
    int N =1;
    double y0[N], y1[N];

    y0[0]= 1.0;                                      /* initial position */

    param_struct *ps = (param_struct *) malloc( sizeof(param_struct) );
    ps->N = 1;

    runge4(0.0, 5.0,  4, y0, y1,  N, f42, ps);

    printf("y1L %f \n ", y1[0]);

}
void runge4(double t0, double t1, double dt, double * y0, double * y1, int N, int f(double, double *, double *, void *),
          void * params )
{

    // because the loop starts at y_n+1, use the values of y0 as initial values
    // for y_n
    double yt[N];
    for (int i = 0; i < N; i++) {
        yt[i] = y0[i];
    }


    double h=dt/2.0,          
           temp1[N], temp2[N], temp3[N],       
           k1[N], k2[N], k3[N],k4[N];    
    int i;

    for (double t = t0 + dt; t<=t1 ; t += dt)                     
    {
        f(t, yt, k1, params);
        for(i = 0; i < N; i++) 
        {
            k1[i] *= dt;
        }

        for(i = 0; i < N; i++) 
        {
            temp1[i] = yt[i] + 0.5 * k1[i];
        }

        f(t+(dt * 0.5), temp1, k2, params);

        for (i = 0; i < N; i++) 
        {
            k2[i] *= dt;
        }

        for (i = 0; i < N; i++) 
        {
            temp2[i] = yt[i] + 0.5 * k2[i];
        }

        f(t + (dt * 0.5), temp2, k3, params);

        for (i = 0; i < N; i++) {
            k3[i] *= dt;
        }

        for (i = 0; i < N; i++) {
            temp3[i] = yt[i] + k3[i];
        }

        f(t + dt, temp3, k4, params);
        
        for (i = 0; i < N; i++) 
        {
            k4[i] *= dt;
        }

        for (i=0; i<N; i++) 
        {
            yt[i]+=( k1[i] + 2 * k2[i] + 2 * k3[i] + k4[i])/6.0;
        }
        printf("%f\n",yt[0]);
    }

        // Put all final values into the y1 array
        for (i=0;i<N;i++) 
        {
            y1[i] = yt[i];
        }
}

int f42(double t, double * y, double * dy, void *params)
{
    for(int i = 0; i < ((param_struct*)params)->N; i++){
        dy[i] = y[i];
    }
    return 0;
}
double f4(double t, double y[])
{
    return(y[0]);     /* derivative of first equation */
}
