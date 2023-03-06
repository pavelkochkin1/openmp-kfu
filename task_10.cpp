#include <iostream>
#include <omp.h>
#include "CustomFunc.h"

using namespace std;

int get_min(int** M, int n, int m, int thread=8){
    int min = INT_MAX;

    #pragma omp parallel for num_threads(thread)
    for(int i = 0; i < n; i++) {
        int local_min = INT_MAX;
        for(int j = 0; j < m; j++) {
            if (local_min > M[i][j]) {
                local_min = M[i][j];
            }
        }
        #pragma omp critical
        if (min > local_min) {
            min = local_min;
        }
    }

    return min;
}

int get_max(int** M, int n, int m, int thread=8){
    int max = INT_MIN;

    #pragma omp parallel for num_threads(thread)
    for(int i = 0; i < n; i++) {
        int local_max = INT_MIN;
        for(int j = 0; j < m; j++) {
            if (local_max < M[i][j]) {
                local_max = M[i][j];
            }
        }
        #pragma omp critical
        if (max < local_max) {
            max = local_max;
        }
    }

    return max;
}

int get_max_reduction(int** M, int n, int m, int thread=8){
    int res = INT16_MIN;

    #pragma omp parallel for reduction(max:res)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (res < M[i][j])
                res = M[i][j];

    return res;
}

int get_min_reduction(int** M, int n, int m, int thread=8){
    int res = INT16_MAX;

    #pragma omp parallel for reduction(min:res)
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (res > M[i][j])
                res = M[i][j];

    return res;
}

int main() {
    int N = 6, M = 8;
    
    int** matr = CustomFunc::get_rand_matrix(N, M, 1000);
    CustomFunc::show_matrix(matr, N, M);

    int min = get_min(matr, N, M);
    int max = get_max(matr, N, M);
    printf("Min=%d; Max=%d\n", min, max);

    min = get_min_reduction(matr, N, M);
    max = get_max_reduction(matr, N, M);
    printf("MinRed=%d; MaxRed=%d\n", min, max);

    return 0;
}