#include <iostream>
#include <omp.h>
#include "CustomFunc.h"

using namespace std;


int main() {

    int* a = new int [12];
    int* b = new int [12];
    int* c = new int [12];

    #pragma omp parallel num_threads(3)
    {   
        int ts = omp_get_num_threads();
        int tn = omp_get_thread_num();

        #pragma omp for schedule(static, 4)
        for (int i = 0; i < 12; i++){
            a[i] = rand() % 100;
            b[i] = rand() % 100;

            printf("TS[%d]:TN[%d]: a[%d]=%d, b[%d]=%d\n", ts, tn, i, a[i], i, b[i]);
        }
    }
    
    CustomFunc::show_array(a, 12);
    CustomFunc::show_array(b, 12);
    cout << endl;
    

    #pragma omp parallel num_threads(4)
    {   
        int ts = omp_get_num_threads();
        int tn = omp_get_thread_num();
        
        #pragma omp for schedule(dynamic, 3)
        for (int i = 0; i < 12; i++){
            c[i] = a[i] + b[i];

            printf("TS[%d]:TN[%d]: c[%d]=%d\n", ts, tn, i, c[i]);
        }
    }

    CustomFunc::show_array(c, 12);
    cout << endl;

    return 0;
}