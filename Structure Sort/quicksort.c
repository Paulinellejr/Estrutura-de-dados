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
    int vetor[] = {10, 7, 8, 9, 1, 5};
    int tamanho = 6;

    printf("Vetor original: ");
    imprimirVetor(vetor, tamanho);

    quicksort(vetor, 0, tamanho - 1);

    printf("Vetor ordenado: ");
    imprimirVetor(vetor, tamanho);

    return 0;
}
