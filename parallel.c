// Code taken from the following git repository: https://github.com/hemanth-kumarv/Bucketsort-in-C/blob/master/bucketsort.c
// Author: hemanth-kumarv
// 10 Mar 2019

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000


void Build_Array(int array[], int n){
    int max = 1000;
    for (int i = 0; i < n; i++){
        array[i] = max;
        max--;
    }
}


void Bucket_Sort(int array[], int n, int max, int min) {

    int i, j = 0;
    int cpos[max+1], cneg[-(min-1)];

    #pragma omp parallel for
    for (i = 0; i <= max; i++)
        cpos[i] = 0;

    #pragma omp parallel for
    for (i = 0; i <= -(min-1); i++)
        cneg[i] = 0;

    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        if (array[i] >= 0)
            (cpos[array[i]])++;
        else
            (cneg[-array[i]])++;
    }

    #pragma omp parallel for
    for (i = -min; i > 0; i--)
        for (; cneg[i] > 0; (cneg[i])--){
            #pragma omp critical
            array[j++] = -i;
        }

    #pragma omp parallel for
    for (i = 0; i <= max; i++)
        for (; cpos[i] > 0; (cpos[i])--){
            #pragma omp critical
            array[j++] = i;
        }

}


int main() {
    int array[N], i, n = N, max = 0, min = 0;
    double t_start, t_wall_clock;

    Build_Array(array, n);
    
    for (i = 0; i < n; i++) {
        if (array[i] > max)
            max = array[i];
        if (array[i] < min)
            min = array[i];
    }

    if (min >= 0)
        min = 0;

    t_start = omp_get_wtime();
    Bucket_Sort(array, n, max, min);
    t_wall_clock = omp_get_wtime() - t_start;
    printf("Time: %f\n", t_wall_clock);

    return 0;
}
