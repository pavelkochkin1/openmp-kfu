#include <iostream>
#include <omp.h>
#include "CustomFunc.h"

using namespace std;

int get_min(int** M, int n, int m, int thread=8){
    int min = INT16_MAX;

    #pragma omp parallel for num_threads(thread)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                #pragma omp critical
                if (min > M[i][j])
                    min = M[i][j];

    return min;
}

int get_max(int** M, int n, int m, int thread=8){
    int max = INT16_MIN;

    #pragma omp parallel for num_threads(thread)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                #pragma omp critical
                if (max < M[i][j])
                    max = M[i][j];
    
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