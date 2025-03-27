#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int *array;
    int tamanho;
    int capacidade;
} MaxHeap;

int pai(int i)
{
    return (i - 1) / 2;
}

int esquerdo(int i)
{
    return 2 * i + 1;
}

int direito(int i)
{
    return 2 * i + 2;
}

void troca(MaxHeap *heap, int i, int j)
{
    int aux = heap->array[i];
    heap->array[i] = heap->array[j];
    heap->array[j] = aux;
}

void maxHeapfy(MaxHeap *heap, int i)
{
    int maior = i;
    int l = esquerdo(i);
    int r = direito(i);

    if (l < heap->tamanho && heap->array[l] > heap->array[maior])
    {
        maior = l;
    }
    if (r < heap->tamanho && heap->array[r] > heap->array[maior])
    {
        maior = r;
    }
    if (maior != i)
    {
        troca(heap, i, maior);
        maxHeapfy(heap, maior);
    }
}

void constroiHeapMax(MaxHeap *heap)
{
    for (int i = (heap->tamanho / 2) - 1; i >= 0; i--)
    {
        maxHeapfy(heap, i);
    }
}

void heapSort(MaxHeap *heap)
{
    constroiHeapMax(heap);
    int tamanhoOriginal = heap->tamanho;
    for (int i = tamanhoOriginal - 1; i > 0; i--)
    {
        troca(heap, 0, i);
        heap->tamanho--;
        maxHeapfy(heap, 0);
    }
    heap->tamanho = tamanhoOriginal;
}

int retiraMaximo(MaxHeap *heap)
{
    if (heap->tamanho < 1)
    {
        printf("ERRO: Heap vazia\n");
        return INT_MIN;
    }
    int max = heap->array[0];
    heap->array[0] = heap->array[heap->tamanho - 1];
    heap->tamanho--;
    maxHeapfy(heap, 0);
    return max;
}

void incrementaChave(MaxHeap *heap, int i, int chave)
{
    if (chave < heap->array[i])
    {
        printf("ERRO: Nova chave é menor que a chave atual\n");
        return;
    }
    heap->array[i] = chave;
    while (i > 0 && heap->array[pai(i)] < heap->array[i])
    {
        troca(heap, i, pai(i));
        i = pai(i);
    }
}

void inserirHeapMax(MaxHeap *heap, int chave)
{
    if (heap->tamanho == heap->capacidade)
    {

        heap->capacidade *= 2;
        heap->array = (int *)realloc(heap->array, heap->capacidade * sizeof(int));
        if (!heap->array)
        {
            printf("ERRO: Falha ao realocar memória\n");
            exit(EXIT_FAILURE);
        }
    }
    heap->array[heap->tamanho] = INT_MIN;
    heap->tamanho++;
    incrementaChave(heap, heap->tamanho - 1, chave);
}

void imprimeHeap(MaxHeap *heap)
{
    for (int i = 0; i < heap->tamanho; i++)
    {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}

int main()
{
    MaxHeap heap;
    heap.tamanho = 0;
    heap.capacidade = 5;
    heap.array = (int *)malloc(heap.capacidade * sizeof(int));

    inserirHeapMax(&heap, 4);
    inserirHeapMax(&heap, 10);
    inserirHeapMax(&heap, 3);
    inserirHeapMax(&heap, 5);
    inserirHeapMax(&heap, 1);

    printf("Array antes do heapify:\n");
    imprimeHeap(&heap);

    constroiHeapMax(&heap);
    printf("Heap construída:\n");
    imprimeHeap(&heap);

    printf("Ordenando com HeapSort:\n");
    heapSort(&heap);
    imprimeHeap(&heap);

    free(heap.array);
    return 0;
}
