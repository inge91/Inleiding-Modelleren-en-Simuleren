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

int main(int argc, const char *argv[])
{
    double y0[1] = {0};
    double y1[1];

    param_struct *ps = (param_struct *) malloc( sizeof(param_struct) );
    ps->N = 1;

    Euler(0, 10, 1, y0, y1, 1, &f, (void*) ps);

    printf("%f\n", y1[0]);
}
