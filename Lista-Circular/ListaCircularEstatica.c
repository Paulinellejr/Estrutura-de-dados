#include <stdio.h>
#include <stdlib.h>

#define MAX 5 // Tamanho máximo da lista

typedef struct
{
    int array;  // Array de nós
    int inicio; // Índice do início da lista
    int fim;    // Índice do final da lista
    int quant;
    int tam
} ListaCircular;

// Função para inicializar a lista
void inicializaLista(ListaCircular *lista)
{
    lista->array = (int)malloc(sizeof(int));
    lista->inicio = -1;
    lista->fim = -1;
}

// Função para verificar se a lista está vazia
int listaVazia(ListaCircular *lista)
{
    return lista->inicio == -1;
}

// Função para verificar se a lista está cheia
int listaCheia(ListaCircular *lista)
{
    return lista->fim == lista->tam - 1;
}

// Função para inserir no final
void insereFinal(ListaCircular *lista, int chave)
{

    if (listaCheia(lista))
    {
        printf("Lista cheia, não é possível inserir!\n");
        return;
    }
    lista->array[lista->fim + 1] = chave;
    if (listaVazia(lista))
    {
        lista->inicio = novo; // Se a lista estiver vazia, o novo nó é o início
    }
    else
    {
        lista->nos[lista->fim].prox = novo; // O último nó aponta para o novo nó
    }
    lista->nos[novo].prox = lista->inicio; // O novo nó aponta de volta para o início, mantendo a circularidade
    lista->fim = novo;                     // Atualiza o fim da lista
}

// Função para remover no início
void removeInicio(ListaCircular *lista)
{
    if (listaVazia(lista))
    {
        printf("Lista vazia, não há nada para remover!\n");
        return;
    }

    int aux = lista->inicio;
    if (lista->inicio == lista->fim)
    {
        lista->inicio = lista->fim = -1; // Se houver apenas um nó, a lista fica vazia
    }
    else
    {
        lista->inicio = lista->nos[lista->inicio].prox; // O início agora é o próximo nó
    }

    printf("Removido: %d\n", lista->nos[aux].chave);
    lista->nos[aux].prox = -1; // Libera o nó removido
}

// Função para imprimir a lista
void imprimeLista(ListaCircular *lista)
{
    if (listaVazia(lista))
    {
        printf("Lista vazia!\n");
        return;
    }

    int i = lista->inicio;
    do
    {
        printf("%d -> ", lista->nos[i].chave);
        i = lista->nos[i].prox;
    } while (i != lista->inicio);
    printf("(inicio)\n");
}

int main()
{
    ListaCircular lista;
    inicializaLista(&lista);

    insereFinal(&lista, 10);
    insereFinal(&lista, 20);
    insereFinal(&lista, 30);
    insereFinal(&lista, 40);

    imprimeLista(&lista); // Esperado: 10 -> 20 -> 30 -> 40 -> (inicio)

    removeInicio(&lista); // Remove o primeiro nó
    imprimeLista(&lista); // Esperado: 20 -> 30 -> 40 -> (inicio)

    return 0;
}
