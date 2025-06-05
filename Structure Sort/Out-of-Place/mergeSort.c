#include <stdio.h>
#include <stdlib.h>
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void mergeSort(int *A, int inicio, int fim)
{
    if (inicio < fim)
    {
        int meio = (inicio + fim) / 2;
        mergeSort(A, inicio, meio);

        mergeSort(A, meio + 1, fim);
        merge(A, inicio, meio, fim);
    }
}

void merge(int A[], int inicio, int meio, int fim)
{
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    int L[n1];
    int R[n2];
    for (int i = 0; i < n1; i++)
    {
        L[i] = A[inicio + i];
    }
    for (int j = 0; j < n1; j++)
    {
        R[j] = A[meio + 1 + j];
    }
    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i++];
        }
        else
        {
            A[k] = R[j++];
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
