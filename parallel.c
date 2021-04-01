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


double Original_BS(int array[], int n, int max, int min) {

    int i, j = 0;
    int cpos[max+1], cneg[-(min-1)];
    double t_start, t_wall_clock, time = 0;

    t_start = omp_get_wtime();
    for (i = 0; i <= max; i++)
        cpos[i] = 0;
    for (i = 0; i <= -(min-1); i++)
        cneg[i] = 0;
    t_wall_clock = omp_get_wtime() - t_start;
    time += t_wall_clock;
    printf("Part 1: %f\n", t_wall_clock);

    t_start = omp_get_wtime();
    for (i = 0; i < n; i++) {
        if (array[i] >= 0)
            (cpos[array[i]])++;
        else
            (cneg[-array[i]])++;
    }
    t_wall_clock = omp_get_wtime() - t_start;
    time += t_wall_clock;
    printf("Part 2: %f\n", t_wall_clock);

    t_start = omp_get_wtime();
    for (i = -min; i > 0; i--)
        for (; cneg[i] > 0; (cneg[i])--)
            array[j++] = -i;

    for (i = 0; i <= max; i++)
        for (; cpos[i] > 0; (cpos[i])--)
            array[j++] = i;
    
    t_wall_clock = omp_get_wtime() - t_start;
    time += t_wall_clock;
    printf("Part 3: %f\n", t_wall_clock);

    return time;
}


double Parallel_BS(int array[], int n, int max, int min) {

    int i, j = 0;
    int cpos[max+1], cneg[-(min-1)];
    double t_start, t_wall_clock, time = 0;

    t_start = omp_get_wtime();
    #pragma omp parallel for
    for (i = 0; i <= max; i++)
        cpos[i] = 0;

    #pragma omp parallel for
    for (i = 0; i <= -(min-1); i++)
        cneg[i] = 0;
    t_wall_clock = omp_get_wtime() - t_start;
    time += t_wall_clock;
    printf("Part 1: %f\n", t_wall_clock);

    t_start = omp_get_wtime();
    #pragma omp parallel for
    for (i = 0; i < n; i++) {
        if (array[i] >= 0)
            (cpos[array[i]])++;
        else
            (cneg[-array[i]])++;
    }
    t_wall_clock = omp_get_wtime() - t_start;
    time += t_wall_clock;
    printf("Part 2: %f\n", t_wall_clock);

    t_start = omp_get_wtime();
    #pragma omp parallel for
    for (i = -min; i > 0; i--)
        for (; cneg[i] > 0; (cneg[i])--)
            array[j++] = -i;

    #pragma omp parallel for
    for (i = 0; i <= max; i++)
        for (; cpos[i] > 0; (cpos[i])--)
            array[j++] = i;
    
    t_wall_clock = omp_get_wtime() - t_start;
    time += t_wall_clock;
    printf("Part 3: %f\n", t_wall_clock);

    return time;
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

    printf("Original\n");
    s_original = omp_get_wtime();
    double time_o = Original_BS(array, n, max, min);
    t_original = omp_get_wtime() - s_original;

    printf("\nParallel\n");
    s_parallel = omp_get_wtime();
    double time_p = Parallel_BS(array, n, max, min);
    t_parallel = omp_get_wtime() - s_parallel;
    
    printf("\nSpeedup: %f/%f = %f\n", time_o, time_p, time_o / time_p);
    printf("Speedup: %f/%f = %f\n", t_original, t_parallel, t_original / t_parallel);

    return 0;
}
