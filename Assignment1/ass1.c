#include <stdio.h>

int main(void)
{
    
    // Unsigned char byte is the size of a byte?
    float f;
    printf("The size of a float: %d\n", sizeof(f));
    double d;
    printf("The size of a double: %d\n", sizeof(d));
    long double ld;
    printf("The size of a long double: %d\n", sizeof(ld));

    //Calculating the smalles possible precision between any two numbers
    float i = 1.0;
    printf("%f\n", i/2.0);
    float j;
    // is only an approximation of the machine precision
    while( i != 0.0 ){
        i = j;
        //printf("%f\n", j);
        i / 2.0;
    }
    printf("Machine precision for floats: %f", j);
    double i = 1.0;
    printf("%f\n", i/2.0);
    double k;
    // is only an approximation of the machine precision
    while( i != 0.0 ){
        i = k;
        //printf("%f\n", j);
        i / 2.0;
    }
    printf("Machine precision for doubles: %f" , k);
    long double i = 1.0;
    printf("%f\n", i/2.0);
    long double l;
    // is only an approximation of the machine precision
    while( i != 0.0 ){
        i = l;
        i / 2.0;
    }
    printf("Machine precision for long doubles: %f", l);
    


    return 0;
    
}
