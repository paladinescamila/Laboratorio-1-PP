// Code taken from the following git repository: https://github.com/hemanth-kumarv/Bucketsort-in-C/blob/master/bucketsort.c
// Author: hemanth-kumarv
// 10 Mar 2019

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000


void buildArray(int array[], int n){
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


int main() {
    int array[N], i, n, max, min, iter = N/20;
    double t_start, t_wall_clock;
    
    for (n = iter; n <= N; n += iter) {

        max = 0;
        min = 0;

        buildArray(array, n);
        
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
        printf("n = %d \t time = %f\n", n, t_wall_clock);
        // printf("%d & %f \\\\ \n", n, t_wall_clock);
        // printf("%d %f\n", n, t_wall_clock);
    }

    return 0;
}
