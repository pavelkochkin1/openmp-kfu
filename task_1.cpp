#include <iostream>
#include <omp.h>

using namespace std;


int main() {
    int numthreads = 8;
    
    #pragma omp parallel num_threads(numthreads) 
    {
        int nt = omp_get_num_threads();
        int tn = omp_get_thread_num();
        printf("Hello World! MaxThreads=%d. ThreadNum=%d.\n", nt, tn);
    }

    return 0;
}