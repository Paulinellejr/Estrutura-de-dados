#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int chave;
    struct no *prox;
} No;

No *criaNo(int ch)
{
    No *novo = (No *)malloc(sizeof(No));
    if (!novo)
    {
        printf("ERRO: não foi possível fazer a alocação");
        exit(1);
    }
    novo->chave = ch;
    novo->prox = novo;
    return novo;
}

No *insereInicio(No *L, int ch)
{
    No *novo = criaNo(ch);
    if (L == NULL)
        return novo;
    novo->prox = L->prox;
    L->prox = novo;
    return L;
}

No *insereFinal(No *L, int ch)
{
    No *novo = criaNo(ch);
    if (L == NULL)
        return novo;
    novo->prox = L->prox;
    L->prox = novo;
    L = novo;
    return L;
}

No *removeInicio(No *L)
{
    No *aux = L;
    if (L == NULL)
    {
        return NULL;
    }
    else
    {
        if (aux->prox == aux)
        {
            free(aux);
            return NULL;
        }
        else
        {
            aux = aux->prox;
            L->prox = aux->prox;
            free(aux);
            return L;
        }
    }
}

No *removeFinal(No *L)
{
    No *aux = L;

    if (L == NULL)
        return NULL;

    if (L->prox == L)
    {
        free(aux);
    }

    while (aux->prox != L)
    {
        aux = aux->prox;
    }

    L = aux;
    aux = L->prox;
    L->prox = aux->prox;
    free(aux);

    return L;
}

void imprime(No *L)
{
    No *aux = L;
    if (L == NULL)
    {
        printf("lista vazia!\n");
    }
    else
    {
        do
        {
            aux = aux->prox;
            printf("%d ", aux->chave);
        } while (aux != L);
        printf("\n");
    }
}

int main()
{
    No *lista = NULL;

    lista = insereInicio(lista, 10);
    lista = insereInicio(lista, 20);
    imprime(lista);

    lista = insereFinal(lista, 30);
    lista = insereFinal(lista, 40);
    imprime(lista);

    lista = removeInicio(lista);
    imprime(lista);

    lista = removeFinal(lista);
    imprime(lista);

    return 0;
}
