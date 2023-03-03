#include <iostream>
#include <omp.h>

using namespace std;


int main() {
    int a = 0, b = 0;

    printf("a = %d, b = %d\n", a, b);
    #pragma omp parallel num_threads(2) private(a) firstprivate(b)
    {   
        int tn = omp_get_thread_num();
        a += tn;
        b += tn;
        printf("a = %d, b = %d\n", a, b);
    }

    printf("\na = %d, b = %d\n\n", a, b);

    #pragma omp parallel num_threads(4) shared(a) private(b)
    {   
        int tn = omp_get_thread_num();
        a -= tn;
        b -= tn;
        printf("a = %d, b = %d\n", a, b);
    }

    printf("a = %d, b = %d\n", a, b);

    return 0; 
}