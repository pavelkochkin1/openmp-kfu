#include <iostream>
#include <omp.h>

using namespace std;

void approach_1(int numthreads){
    int i = numthreads - 1;

    #pragma omp parallel num_threads(numthreads)   
    while (i >= 0){
        int tn = omp_get_thread_num();
        // printf("TN: %d, I=%d\n", tn, i);
        if (tn == i){
            printf("TN: %d\n", tn);
            #pragma atomic
            i--;
        }
    }
}

void approach_2(int numthreads){
    for (int i = numthreads - 1; i >= 0; i--){
        #pragma omp parallel num_threads(numthreads)
        {
            int tn = omp_get_thread_num();
            if (i == tn)
                printf("TN: %d\n", tn);
        }
    }
}

void approach_3(int numthreads){
    #pragma omp parallel num_threads(numthreads)
    {   
        for(int i = numthreads - 1; i >= 0; i--){
            int tn = omp_get_thread_num();
            #pragma omp barrier
            if(i == tn)
                printf("TN: %d\n", tn);
        }
    }
}

void approach_4(int numthreads){
    int i = numthreads - 1;
    #pragma omp parallel num_threads(numthreads)
    {
        while(i >= 0){
            printf("i=%d\n", i);
            int tn = omp_get_thread_num();
            #pragma omp single
            if (i == tn){
                printf("TN: %d\n", tn);
                i--;
            }
        }
    }
}


int main() {
    int numthreads = 8;
    
    approach_4(numthreads);
    

    return 0;
}