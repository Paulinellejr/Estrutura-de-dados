#include <stdio.h>
#include <stdlib.h>

void countingSort(int A[], int n)
{
    int k = A[0];
    for (int i = 0; i < n; i++)
    {
        if (A[i] > k)
        {
            k = A[i];
        }
    }
    int b[n - 1];
    int c[k];
    for (int i = 0; i < n; i++)
        c[i] = 0;
    for (int i = 0; i < n; i++)
        c[A[i]] = c[A[i]] + 1;
    for (int i = 0; i < k; i++)
        c[i] = c[i] + c[i - 1];
    for (int j = n - 1; j > 0; j--)
    {
        b[c[A[j]] - 1] = A[j];
        c[A[j]] = c[A[j]] - 1;
    }
    for (int i = 0; i < n; i++)
        A[i] = b[i];
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void printArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main()
{
    int Arr[] = {10, 7, 2, 90, 1, 5};
    int size = 6;

    printf("Original vector: ");
    printArray(Arr, size);
    countingSort(Arr, size);

    printf("Ordered vector: ");
    printArray(Arr, size);

    return 0;
}
