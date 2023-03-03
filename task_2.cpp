#include <iostream>
#include <omp.h>

using namespace std;


int main() {
    int num_threads = 3;
    #pragma omp parallel if(num_threads > 2) num_threads(num_threads)
    {   
        int nt = omp_get_num_threads();
        int tn = omp_get_thread_num();
        printf("MaxThreads=%d. ThreadNum=%d.\n", nt, tn);
    }
    cout << endl;

    num_threads = 2;
    #pragma omp parallel if(num_threads > 2) num_threads(num_threads)
    {   
        int nt = omp_get_num_threads();
        int tn = omp_get_thread_num();
        printf("MaxThreads=%d. ThreadNum=%d.\n", nt, tn);
    }

    return 0; 
}