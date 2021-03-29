// Código sacado del siguiente repositorio en git https://github.com/hemanth-kumarv/Bucketsort-in-C/blob/master/bucketsort.c
// Author: hemanth-kumarv
// 10 Mar 2019

#include <stdio.h>
#include <stdlib.h>


void Bucket_Sort(int array[], int n, int max, int min)
{
    int i, j = 0;
    int cpos[max+1], cneg[-(min-1)];
    for (i = 0; i <= max; i++)
        cpos[i] = 0;
    for (i = 0; i <= -(min-1); i++)
        cneg[i] = 0;

    for (i = 0; i < n; i++)
    {
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

int main()
{
    int array[100], i, num, max = 0, min = 0;
    printf("Enter the size of array : ");
    scanf("%d", &num);
    printf("Enter the %d elements to be sorted:\n",num);
    for (i = 0; i < num; i++)
        scanf("%d", &array[i]);
    for (i = 0; i < num; i++)
    {
        if (array[i] > max)
            max = array[i];
        if (array[i] < min)
            min = array[i];
    }
    if (min >= 0)min = 0;
    printf("\nThe array of elements before sorting : \n");
    for (i = 0; i < num; i++)
        printf("%d ", array[i]);
    printf("\nThe array of elements after sorting : \n");
    Bucket_Sort(array, num, max, min);
    for (i = 0; i < num; i++)
    {
        printf("%d ", array[i]);
    }

    return 0;
}
