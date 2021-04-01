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

    for (i = 0; i <= max; i++)
        cpos[i] = 0;
    for (i = 0; i <= -(min-1); i++)
        cneg[i] = 0;

    for (i = 0; i < n; i++) {
        if (array[i] >= 0)
            (cpos[array[i]])++;
        else
            (cneg[-array[i]])++;
    }

    for (i = -min; i > 0; i--)
        for (; cneg[i] > 0; (cneg[i])--)
            array[j++] = -i;

    for (i = 0; i <= max; i++)
        for (; cpos[i] > 0; (cpos[i])--)
            array[j++] = i;
}


void Parallel_Bucket_Sort(int array[], int n, int max, int min) {

    int i, j = 0;
    int cpos[max+1], cneg[-(min-1)];

    for (i = 0; i <= max; i++)
        cpos[i] = 0;
    for (i = 0; i <= -(min-1); i++)
        cneg[i] = 0;

    for (i = 0; i < n; i++) {
        if (array[i] >= 0)
            (cpos[array[i]])++;
        else
            (cneg[-array[i]])++;
    }

    for (i = -min; i > 0; i--)
        for (; cneg[i] > 0; (cneg[i])--)
            array[j++] = -i;

    for (i = 0; i <= max; i++)
        for (; cpos[i] > 0; (cpos[i])--)
            array[j++] = i;
}


int main() {
    int array[N], i, n = N, max = 0, min = 0;
    double s_original, s_parallel, t_original, t_parallel;

    Build_Array(array, n);
    
    for (i = 0; i < n; i++) {
        if (array[i] > max)
            max = array[i];
        if (array[i] < min)
            min = array[i];
    }

    if (min >= 0)
        min = 0;

    s_original = omp_get_wtime();
    Bucket_Sort(array, n, max, min);
    t_original = omp_get_wtime() - s_original;
    
    s_parallel = omp_get_wtime();
    Parallel_Bucket_Sort(array, n, max, min);
    t_parallel = omp_get_wtime() - s_parallel;

    printf("Speedup = %f\n", t_original / t_parallel);

    return 0;
}
