#include <iostream>
#include <omp.h>
#include "CustomFunc.h"

using namespace std;

int max_of_mult(int* arr, int n, int target, int num_threads=8){
    omp_lock_t max_lock;
    int max = INT16_MIN;

    omp_init_lock(&max_lock);

    #pragma parallel for num_threads(num_threads)
    for (int i = 0; i < n; i++){
        omp_set_lock(&max_lock);
        if (arr[i] % target == 0 & arr[i] > max)
            max = arr[i];
        omp_unset_lock(&max_lock);
    }
    
    return max;
}


int main() {
    int N = 10;
    
    int* arr = CustomFunc::get_rand_array(N, 100);
    CustomFunc::show_array(arr, N);

    int max_paral = max_of_mult(arr, N, 7);

    printf("Max = %d\n", max_paral);

    return 0;
}