#include <stdio.h>
#include <stdlib.h>

#include "differentials.h"

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

    printf("Outcome should be 10\n");
    for (double i = 0.5; i <= 1.5 ; i += 0.5) {
        printf("Experimentation with dt = %f\n", i );
        Euler(0, 10, i, y0, y1, 1, &f, (void*) ps);
        printf("Euler gives: %f\n", y1[0]);

        RungeKutta2(0, 10, i, y0, y1, 1, &f, (void*) ps);
        printf("RungeKutta2 gives: %f\n", y1[0]);
        
        RungeKutta4(0, 10, i, y0, y1, 1, &f, (void*) ps);
        printf("RungeKutta4 gives: %f\n\n", y1[0]);
    }

        printf("Experimentation with dt = %d\n", 10 );
        Euler(0, 10, 10, y0, y1, 1, &f, (void*) ps);
        printf("Euler gives: %f\n", y1[0]);

        RungeKutta2(0, 10, 10, y0, y1, 1, &f, (void*) ps);
        printf("RungeKutta2 gives: %f\n", y1[0]);
        
        RungeKutta4(0, 10, 10, y0, y1, 1, &f, (void*) ps);
        printf("RungeKutta4 gives: %f\n\n", y1[0]);


        double iter[] = {0.05, 0.1, 0.2, 0.5, 1, 5};
        int iter_size = 6;

        printf("Outcome should be 50\n");
        for (int i = 0; i <= iter_size ; i++) {
            printf("Experimentation with dt = %f\n", iter[i] );
            Euler(0, 10, iter[i], y0, y1, 1, &f2, (void*) ps);
            printf("Euler gives: %f\n", y1[0]);

            RungeKutta2(0, 10, iter[i], y0, y1, 1, &f2, (void*) ps);
            printf("RungeKutta2 gives: %f\n", y1[0]);
            
            RungeKutta4(0, 10, iter[i], y0, y1, 1, &f2, (void*) ps);
            printf("RungeKutta4 gives: %f\n\n", y1[0]);
        }
        
        printf("Outcome should be approximately 144\n");
        // We now start at y0 = 1
        y0[0] =1;

        for (int i = 0; i <= iter_size ; i++) {
            printf("Experimentation with dt = %f\n", iter[i] );
            Euler(0, 5, iter[i], y0, y1, 1, &f3, (void*) ps);
            printf("Euler gives: %f\n", y1[0]);

            RungeKutta2(0, 5, iter[i], y0, y1, 1, &f3, (void*) ps);
            printf("RungeKutta2 gives: %f\n", y1[0]);
            
            RungeKutta4(0, 5, iter[i], y0, y1, 1, &f3, (void*) ps);
            printf("RungeKutta4 gives: %f\n\n", y1[0]);
        }


}
