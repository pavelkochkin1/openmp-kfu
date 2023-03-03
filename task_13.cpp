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
            int tn = omp_get_thread_num();
            #pragma omp barrier
            #pragma omp single
            if (i == tn){
                printf("TN: %d\n", tn);
                i--;
            }
        }
    }
}

void approach_5(int numthreads){
    omp_lock_t lock;
    omp_init_lock(&lock);

    int i = numthreads - 1;

    #pragma omp parallel num_threads(numthreads)
    {
        while(i >= 0){
            int tn = omp_get_thread_num();
            omp_set_lock(&lock);
            if (i == tn){
                printf("TN: %d\n", tn);
                i--;
            }
            omp_unset_lock(&lock);
        }
    }
}

void approach_6(int numthreads){
    int i = numthreads - 1;

    #pragma omp parallel num_threads(numthreads)
    {
        while(i >= 0){
            int tn = omp_get_thread_num();
            #pragma omp critical
            if (i == tn){
                printf("TN: %d\n", tn);
                i--;
            }
        }
    }
}

void approach_7(int numthreads){
    int i = numthreads - 1;

    #pragma omp parallel for num_threads(numthreads)
        for(int j = 0; j <= 100000000; j++)
        {
            int tn = omp_get_thread_num();
            if (i == tn) {
                printf("TN: %d\n", tn);
                #pragma omp atomic
                i--;
            }
        }
}


int main() {
    int numthreads = 8;
    
    approach_7(numthreads);
    
    return 0;
}