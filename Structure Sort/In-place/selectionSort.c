#include <stdio.h>
#include <stdlib.h>
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSort(int A[], int n)
{

    for (int i = 0; i <= n - 2; i++)
    {
        int smallest = i;
        for (int j = i + 1; j < n; j++)
        {
            if (A[j] < A[smallest]) // procura o menor item
            {
                smallest = j;
            }
        }

        if (smallest != i) // substitui o item
        {
            swap(&A[smallest], &A[i]);
        }
    }
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
    selectionSort(Arr, size);

    printf("Ordered vector: ");
    printArray(Arr, size);

    return 0;
}
