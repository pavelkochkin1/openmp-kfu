#include <iostream>
#include <omp.h>
#include "CustomFunc.h"

using namespace std;


int main() {
    int* a = CustomFunc::get_rand_array(10, 100);
    int* b = CustomFunc::get_rand_array(10, 100);

    CustomFunc::show_array(a, 10);
    CustomFunc::show_array(b, 10);

    #pragma omp parallel num_threads(2)
    {   
        if (omp_get_thread_num() == 0){

            int min = CustomFunc::min_array(a, 10);
            printf("Min of a: %d\n", min);

        }else if(omp_get_thread_num() == 1) {

            int max = CustomFunc::max_array(b, 10);
            printf("Max of b: %d\n", max);

        }
    }

    return 0; 
}