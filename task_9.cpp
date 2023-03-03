#include <iostream>
#include <omp.h>
#include "CustomFunc.h"

using namespace std;


int* matrix_mult_vec(int** matr, int* arr, int n, int m){
    int* c = new int [m];

    for (int i = 0; i < n; i++) {
        c[i] = 0;
        for (int j = 0; j < m; j++)
            c[i] += matr[i][j] * arr[j];
    }

    return c;
}

int* matrix_mult_vec_paral(int** matr, int* arr, int n, int m, int num_threads = 4){
    int* c = new int [m];

    #pragma omp parallel num_threads(num_threads)
    {   
        #pragma omp for schedule(dynamic)
        for (int i = 0; i < n; i++) {
            c[i] = 0;
            for (int j = 0; j < m; j++)
                c[i] += matr[i][j] * arr[j];
        }
    }

    return c;
}


int main() {
    int N = 10;
    // int iter = 100;
    
    int** matr = CustomFunc::get_rand_matrix(N, N, 10);
    int* arr = CustomFunc::get_rand_array(N, 10);


    // double mean_time = 0, time;
    // for(int i = 0; i < iter; i++) {
    //     time = omp_get_wtime();

    //     int* c = matrix_mult_vec_paral(matr, arr, N, N, 4);

    //     mean_time += (omp_get_wtime() - time);
    // }
    // printf("Guided mean time on 10 iterations for N=10k: %f", mean_time/iter);

    int* c;

    double prl_time, time, time_start, prl_start;

    do {
        prl_time = 0;
        time = 0;

        printf("N: %d\n", N);

        int** matr = CustomFunc::get_rand_matrix(N, N, 10);
        int* arr = CustomFunc::get_rand_array(N, 10);

        // consistent
        for (int i = 0; i < 100; i++){
            time_start = omp_get_wtime();
            c = matrix_mult_vec(matr, arr, N, N);
            time += omp_get_wtime() - time_start;
        }
        time /= 100;

        // parallel
        for (int i = 0; i < 100; i++){
            prl_start = omp_get_wtime();
            c = matrix_mult_vec_paral(matr, arr, N, N);
            prl_time += omp_get_wtime() - prl_start;
        }
        prl_time /= 100;

        N += 10;
    } while (prl_time > time);
    

    return 0;
}

// Static mean time on 10 iterations for N=10k: 0.056084
// Dynamic mean time on 10 iterations for N=10k: 0.055690 *****- BEST -******
// Guided mean time on 10 iterations for N=10k: 0.055834
// Auto mean time on 10 iterations for N=10k: 0.056273

// Parallel wins consistent after N=60