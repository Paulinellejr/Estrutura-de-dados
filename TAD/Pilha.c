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
        printf("ERRO: nao foi possivel alocar memoria!\n");
        exit(1);
    }
    novo->chave = ch;
    novo->prox = NULL;
    return novo;
}

No *empilha(No *L, int ch)
{
    No *novo = criaNo(ch);
    novo->prox = L;
    return novo;
}

No *desempilha(No *L)
{
    No *aux = L;
    if (L == NULL)
    {
        printf("Pilha vazia! Não é possível desempilhar.\n");
        return NULL;
    }
    L = L->prox;
    free(aux);
    return L;
}

void ImprimePilha(No *L)
{
    No *aux = L;
    if (L == NULL)
    {
        printf("Pilha Vazia!\n");
    }
    else
    {
        printf("Pilha: ");
        while (aux != NULL)
        {
            printf("%d ", aux->chave);
            aux = aux->prox;
        }
        printf("\n");
    }
}

int main()
{
    No *pilha = NULL;

    ImprimePilha(pilha);

    pilha = empilha(pilha, 10);
    pilha = empilha(pilha, 20);
    pilha = empilha(pilha, 30);
    ImprimePilha(pilha);

    pilha = desempilha(pilha);
    ImprimePilha(pilha);

    pilha = desempilha(pilha);
    ImprimePilha(pilha);

    pilha = desempilha(pilha);
    ImprimePilha(pilha);
    return 0;
}
