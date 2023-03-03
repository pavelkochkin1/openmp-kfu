#pragma once
#include <iostream>


namespace CustomFunc
{   
    int* get_rand_array(int n, int r){
        int* a = new int [n];
        for(int i = 0; i < n; i++){
            a[i] = rand() % r;
        }

        return a;
    }

    int** get_rand_matrix(int n, int m, int r){
        int** d = new int* [n];
        for(int i = 0; i < n; i++){
            d[i] = get_rand_array(m, r);
        }

        return d;
    }

    void show_array(int* a, int n){
        for(int i = 0; i < n; i++){
            std::cout << a[i] << " ";
        }
        std::cout << std::endl;
    }

    void show_matrix(int** a, int n, int m){
        for(int i = 0; i < n; i++){
            show_array(a[i], m);
        }
        std::cout << std::endl;
    }

    int min_array(int* a, int n){
        int min = INT16_MAX;
        for(int i = 0; i < n; i++)
            if (a[i] < min) 
                min = a[i];
        return min;
    }

    int max_array(int* a, int n){
        int max = INT16_MIN;
        for(int i = 0; i < n; i++)
            if (a[i] > max) 
                max = a[i];
        return max;
    }

    float mean_of_matrix(int** array, int n, int m){
        int sum = 0;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                sum += array[i][j];

        return sum / (n * m);
    }

    int* min_max_of_array(int** array, int n, int m){
        int* a = new int [2];
        a[0] = INT16_MAX;
        a[1] = INT16_MIN;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(array[i][j] < a[0])
                    a[0] = array[i][j];
                else if(array[i][j] > a[1])
                    a[1] = array[i][j];
            }
        }

        return a;
    }

    int count_multiple_of_3(int** array, int n, int m){
        int count = 0;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(array[i][j]%3 == 0)
                    count++;
            }
        }

        return count;
    }
}