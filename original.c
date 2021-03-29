// Code taken from the following git repository: https://github.com/hemanth-kumarv/Bucketsort-in-C/blob/master/bucketsort.c
// Author: hemanth-kumarv
// 10 Mar 2019

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000


void randomArray(int array[], int n){
    for (int i = 0; i < n; i++)
        array[i] = rand() % 100;
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
    int array[N], i, num = 1000000, max = 0, min = 0;
    randomArray(array, num);

    for (i = 0; i < num; i++) {
        if (array[i] > max)
            max = array[i];
        if (array[i] < min)
            min = array[i];
    }
    if (min >= 0)
        min = 0;
    Bucket_Sort(array, num, max, min);
    return 0;
}
