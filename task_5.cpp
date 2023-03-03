#include <iostream>
#include <omp.h>
#include "CustomFunc.h"

using namespace std;


int main() {
    int** d = CustomFunc::get_rand_matrix(6, 8, 100);
    CustomFunc::show_matrix(d, 6, 8);
    
    #pragma omp parallel sections
    {
        #pragma omp section 
        {
            float mean = CustomFunc::mean_of_matrix(d, 6, 8);
            printf("TN[%d]: Mean = %f\n", omp_get_thread_num(), mean);
        }

        #pragma omp section 
        {
            int* a = CustomFunc::min_max_of_array(d, 6, 8);
            printf("TN[%d]: Min = %d and Max = %d\n", omp_get_thread_num(), a[0], a[1]);
        }

        #pragma omp section 
        {
            int cnt = CustomFunc::count_multiple_of_3(d, 6, 8);
            printf("TN[%d]: Count multiple of three = %d\n", omp_get_thread_num(), cnt);
        }
    }

    return 0; 
}