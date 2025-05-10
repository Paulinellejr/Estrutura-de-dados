#include <stdlib.h>
#include <stdio.h>

void insertionSort(int A[], int n)
{
    int chave;
    for (int i = 1; i < n; i++)
    {
        chave = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > chave)
        {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = chave;
    }
}

void imprimirVetor(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", vetor[i]);
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