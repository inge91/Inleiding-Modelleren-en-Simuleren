#include "time.h"
#include <stdio.h> 
#include <math.h>
#include <string.h>




// speedtest for strings
void float_addition()
{
    
    float k = 100;
    double j;
    clock_t begin_time, end_time;
    double  time_taken2, time_taken3;

    begin_time = clock();

    // 1000 power operations
    for(int i = 0; i < 999999; i ++) {
        j = pow(k, 50);

    }
    end_time = clock();
    
    time_taken2 = (end_time - begin_time) / (double) CLOCKS_PER_SEC;

    printf("Elapsed time of 100000 pow operations: %f seconds \n", time_taken2);

    begin_time = clock();

    // some loop unrolling
    for(int i = 0; i < 99999; i ++) {
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
    }
    end_time = clock();

    time_taken3 = (double)(end_time - begin_time) / (double) CLOCKS_PER_SEC;
    printf("Elapsed time of 10000 pow operations that use loop unrolling: %f seconds \n", time_taken3);

    printf("If we take the time of a single operation by taking the mean of these 100000 operations we get %g seconds or %g ms", time_taken3 / 100000.0, time_taken3 / 100000.0 * 1000);


}

void float_substraction()
{
    float k = 100;

    double j;

    clock_t begin_time, end_time;
    double  time_taken2, time_taken3;

    begin_time = clock();

    // 1000 power operations
    for(int i = 0; i < 999999; i ++) {
        j = pow(k, 50);

    }
    end_time = clock();
    
    time_taken2 = (end_time - begin_time) / (double) CLOCKS_PER_SEC;

    printf("Elapsed time of 100000 pow operations: %f seconds \n", time_taken2);

    begin_time = clock();

    // some loop unrolling
    for(int i = 0; i < 99999; i ++) {
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
    }
    end_time = clock();

    time_taken3 = (double)(end_time - begin_time) / (double) CLOCKS_PER_SEC;
    printf("Elapsed time of 10000 pow operations that use loop unrolling: %f seconds \n", time_taken3);

    printf("If we take the time of a single operation by taking the mean of these 100000 operations we get %g seconds or %g ms", time_taken3 / 100000.0, time_taken3 / 100000.0 * 1000);


}

void float_multiplication()
{
    
    float k = 100;

    double j;

    clock_t begin_time, end_time;
    double  time_taken2, time_taken3;

    begin_time = clock();

    // 1000 power operations
    for(int i = 0; i < 999999; i ++) {
        j = pow(k, 50);

    }
    end_time = clock();
    
    time_taken2 = (end_time - begin_time) / (double) CLOCKS_PER_SEC;

    printf("Elapsed time of 100000 pow operations: %f seconds \n", time_taken2);

    begin_time = clock();

    // some loop unrolling
    for(int i = 0; i < 99999; i ++) {
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
    }
    end_time = clock();

    time_taken3 = (double)(end_time - begin_time) / (double) CLOCKS_PER_SEC;
    printf("Elapsed time of 10000 pow operations that use loop unrolling: %f seconds \n", time_taken3);

    printf("If we take the time of a single operation by taking the mean of these 100000 operations we get %g seconds or %g ms", time_taken3 / 100000.0, time_taken3 / 100000.0 * 1000);



}

void float_division()
{
    
    float k = 100;
    double j;

    clock_t begin_time, end_time;
    double  time_taken2, time_taken3;

    begin_time = clock();

    // 1000 power operations
    for(int i = 0; i < 999999; i ++) {
        j = pow(k, 50);

    }
    end_time = clock();
    
    time_taken2 = (end_time - begin_time) / (double) CLOCKS_PER_SEC;

    printf("Elapsed time of 100000 pow operations: %f seconds \n", time_taken2);

    begin_time = clock();

    // some loop unrolling
    for(int i = 0; i < 99999; i ++) {
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
    }
    end_time = clock();

    time_taken3 = (double)(end_time - begin_time) / (double) CLOCKS_PER_SEC;
    printf("Elapsed time of 10000 pow operations that use loop unrolling: %f seconds \n", time_taken3);

    printf("If we take the time of a single operation by taking the mean of these 100000 operations we get %g seconds or %g ms", time_taken3 / 100000.0, time_taken3 / 100000.0 * 1000);


}


void float_power()
{
    float k = 100;
    double j;

    clock_t begin_time, end_time;
    double  time_taken2, time_taken3;

    begin_time = clock();

    // 1000 power operations
    for(int i = 0; i < 999999; i ++) {
        j = pow(k, 50);

    }
    end_time = clock();
    
    time_taken2 = (end_time - begin_time) / (double) CLOCKS_PER_SEC;

    printf("Elapsed time of 100000 pow operations: %f seconds \n", time_taken2);

    begin_time = clock();

    // some loop unrolling
    for(int i = 0; i < 99999; i ++) {
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
    }
    end_time = clock();

    time_taken3 = (double)(end_time - begin_time) / (double) CLOCKS_PER_SEC;
    printf("Elapsed time of 10000 pow operations that use loop unrolling: %f seconds \n", time_taken3);

    printf("If we take the time of a single operation by taking the mean of these 100000 operations we get %g seconds or %g ms", time_taken3 / 100000.0, time_taken3 / 100000.0 * 1000);


}

void float_squareroot(){

    float k = 100;

    double j;

    clock_t begin_time, end_time;
    double  time_taken2, time_taken3;

    begin_time = clock();

    // 1000 power operations
    for(int i = 0; i < 999999; i ++) {
        j = pow(k, 50);

    }
    end_time = clock();
    
    time_taken2 = (end_time - begin_time) / (double) CLOCKS_PER_SEC;

    printf("Elapsed time of 100000 pow operations: %f seconds \n", time_taken2);

    begin_time = clock();

    // some loop unrolling
    for(int i = 0; i < 99999; i ++) {
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
        j = pow(k, 50);
    }
    end_time = clock();

    time_taken3 = (double)(end_time - begin_time) / (double) CLOCKS_PER_SEC;
    printf("Elapsed time of 10000 pow operations that use loop unrolling: %f seconds \n", time_taken3);

    printf("If we take the time of a single operation by taking the mean of these 100000 operations we get %g seconds or %g ms", time_taken3 / 100000.0, time_taken3 / 100000.0 * 1000);


}


void float_speedtest(){
    float_addition();
    float_substraction();
    float_division();
    float_multiplication();
    float_power();
    float_squareroot();
}


void double_speedtest(){
    double_addition();
    double_substraction();
    double_division();
    double_multiplication();
    double_power();
    double_squareroot();
}

//Calculate the time of different operations
int main(void){

    // Speedtest for all datatypes
    float_speedtest();
    double_speedtest();

    return 0;

}
