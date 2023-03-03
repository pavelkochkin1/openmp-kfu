#include <iostream>
#include <omp.h>
#include "CustomFunc.h"

using namespace std;


int main() {
    int N = 16000;

    int parts[4] = {1, 50, 200, 400};

    int* a = new int [N];
    int* b = new int [N];
    for (int i = 0; i < N; i++)
        a[i] = i;

    double time;

    cout << "STATIC\n";
    for (int i = 0; i < 4; i++){
        time = omp_get_wtime();
        #pragma omp parallel num_threads(8)
        {   

            #pragma omp for schedule(static, parts[i])
            for (int i = 1; i < N - 1; i++)
                b[i] = (a[i-1] + a[i] + a[i+1]) / 3.;

        }
        printf("ExecTime: %f. Parts: %d\n", (omp_get_wtime() - time), parts[i]);
    }
    cout << "\n\n";
    

    cout << "DYNAMIC\n";
    for (int i = 0; i < 4; i++){
        time = omp_get_wtime();
        #pragma omp parallel num_threads(8)
        {   

            #pragma omp for schedule(dynamic, parts[i])
            for (int i = 1; i < N - 1; i++)
                b[i] = (a[i-1] + a[i] + a[i+1]) / 3.;

        }
        printf("ExecTime: %f. Parts: %d\n", (omp_get_wtime() - time), parts[i]);
    }
    cout << "\n\n";


    cout << "GUIDED\n";
    for (int i = 0; i < 4; i++){
        time = omp_get_wtime();
        #pragma omp parallel num_threads(8)
        {   

            #pragma omp for schedule(guided, parts[i])
            for (int i = 1; i < N - 1; i++)
                b[i] = (a[i-1] + a[i] + a[i+1]) / 3.;

        }
        printf("ExecTime: %f. Parts: %d\n", (omp_get_wtime() - time), parts[i]);
    }
    cout << "\n\n";


    cout << "AUTO\n";
    time = omp_get_wtime();
    #pragma omp parallel num_threads(8)
    {   

        #pragma omp for schedule(auto)
        for (int i = 1; i < N - 1; i++)
            b[i] = (a[i-1] + a[i] + a[i+1]) / 3.;

    }
    printf("ExecTime: %f\n", (omp_get_wtime() - time));
    cout << "\n\n";

    return 0;
}

// STATIC
// ExecTime: 0.000331. Parts: 1
// ExecTime: 0.000166. Parts: 50
// ExecTime: 0.000431. Parts: 200
// ExecTime: 0.000196. Parts: 400


// DYNAMIC
// ExecTime: 0.000282. Parts: 1
// ExecTime: 0.000178. Parts: 50
// ExecTime: 0.000161. Parts: 200
// ExecTime: 0.000132. Parts: 400


// GUIDED
// ExecTime: 0.000165. Parts: 1
// ExecTime: 0.000143. Parts: 50
// ExecTime: 0.000121. Parts: 200 ***********************- BEST -**********************
// ExecTime: 0.000262. Parts: 400


// AUTO
// ExecTime: 0.000124