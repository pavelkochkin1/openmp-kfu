#include <iostream>
#include <omp.h>
#include "CustomFunc.h"

using namespace std;


int main() {

    int* a = CustomFunc::get_rand_array(100, 10);
    CustomFunc::show_array(a, 100);

    float mean = 0;

    #pragma omp parallel 
    {   
        int tid = omp_get_thread_num();
        #pragma omp for 
        for (int i = 0; i < 100; i++){
            mean += a[i];
        }
    }
    mean /= 100;
    printf("Mean(classic) = %f\n", mean);


    mean = 0;
    #pragma omp parallel
    {   
        int tid = omp_get_thread_num();
        #pragma omp for reduction(+:mean)
        for (int i = 0; i < 100; i++){
            mean += a[i];
        }
    }
    mean /= 100;
    printf("Mean(reduction) = %f\n", mean);

    return 0;
}