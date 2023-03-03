#include <iostream>
#include <omp.h>
#include "CustomFunc.h"

using namespace std;

int count_of_mult(int* arr, int n, int target, int num_threads=8){
    int cnt = 0;

    #pragma parallel for num_threads(num_threads)
    for (int i = 0; i < n; i++)
        if (arr[i] % target == 0)
            #pragma omp atomic
            cnt++;
    
    return cnt;
}


int main() {
    int N = 30;
    
    int* arr = CustomFunc::get_rand_array(N, 100);
    CustomFunc::show_array(arr, N);

    int cnt = count_of_mult(arr, N, 9);
    printf("Cnt = %d\n", cnt);

    return 0;
}