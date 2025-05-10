#include <stdio.h>

// Função de partição (divide o vetor em dois)
int particionar(int vetor[], int inicio, int fim)
{
    int pivo = vetor[fim]; // pivô é o último elemento
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++)
    {
        if (vetor[j] < pivo)
        {
            i++;
            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }

    int temp = vetor[i + 1];
    vetor[i + 1] = vetor[fim];
    vetor[fim] = temp;
    return i + 1;
}

// Função principal do quicksort (recursiva)
void quicksort(int vetor[], int inicio, int fim)
{
    if (inicio < fim)
    {
        int indicePivo = particionar(vetor, inicio, fim);
        quicksort(vetor, inicio, indicePivo - 1);
        quicksort(vetor, indicePivo + 1, fim);
    }
}

// Função auxiliar para imprimir o vetor
void imprimirVetor(int vetor[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

// Função principal
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
