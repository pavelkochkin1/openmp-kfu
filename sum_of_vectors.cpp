#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    const long int n = 1000000;
    double* a = new double[n];
    double* b = new double[n];
    double* c = new double[n];

    for (int i = 0; i < n; i++){
        a[i] = rand() / RAND_MAX;
        b[i] = rand() / RAND_MAX;
    }
    double time = omp_get_wtime();
    for (int j = 0; j < 100; j++) {
        #pragma omp parallel shared(a, b, c)
        #pragma omp for
        for (int i = 0; i < n; i++) {
            c[i] = a[i] + b[i];
        }
    }
    cout << "Time = " << (omp_get_wtime() - time) << endl;

    return 0;
}