#include <stdio.h>
#include <stdlib.h>

typedef struct no
{
    int chave;
    struct no *ant, *prox;
} No;

No *criaLista()
{
    No *cabeca = (No *)calloc(1, sizeof(No));
    if (!cabeca)
    {
        printf("ERRO de Alocação");
        exit(1);
    }
    return cabeca;
}

No *criaNo(int ch)
{
    No *novo = (No *)malloc(sizeof(No));
    if (!novo)
    {
        printf("Erro de alocação");
        exit(1);
    }
    novo->chave = ch;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}

No *buscaChave(No *L, int valor)
{
    No *aux = L->prox;
    while (aux != NULL && valor != aux->chave)
    {
        aux = aux->prox;
    }
    return aux;
}

void inserirInicio(No *L, int ch)
{
    No *novo = criaNo(ch);
    novo->prox = L->prox;
    novo->ant = L;
    if (L->prox != NULL)
    {
        L->prox->ant = novo;
    }
    else
    {
        L->ant = novo;
    }
    L->prox = novo;
}

void insereFinal(No *L, int ch)
{
    No *novo = criaNo(ch);
    if (L->prox == NULL)
    {
        L->prox = novo;
        novo->ant = L;
    }
    else
    {
        L->ant->prox = novo;
        novo->ant = L->ant;
    }
    L->ant = novo;
}

void removeInicio(No *L)
{
    No *aux = L->prox;
    if (aux != NULL)
    {
        L->prox = aux->prox;
        if (aux->prox != NULL)
        {
            aux->prox->ant = L;
        }
        free(aux);
    }
}

void removeFinal(No *L)
{
    No *aux = L->ant;
    if (aux != NULL)
    {
        L->ant = aux->ant;
        if (aux->ant != NULL)
        {
            aux->ant->prox = NULL;
        }
        else
        {
            L->prox = NULL;
        }
        free(aux);
    }
}

void removeChave(No *L, int ch)
{
    No *aux = buscaChave(L, ch);
    if (aux == NULL)
    {
        printf("Chave %d não encontrada.\n", ch);
        return;
    }
    if (aux->ant != NULL)
    {
        aux->ant->prox = aux->prox;
    }
    if (aux->prox != NULL)
    {
        aux->prox->ant = aux->ant;
    }
    free(aux);
}

void ImprimeLista(No *L)
{
    No *aux = L->prox;
    if (aux == NULL)
    {
        printf("Lista vazia!\n");
    }
    else
    {
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
    No *lista = criaLista();
    int opcao, valor;

    while (opcao != 8)
    {
        printf("\nPainel - Lista Duplamente Encadeada\n");
        printf("1. Inserir no início\n");
        printf("2. Inserir no final\n");
        printf("3. Remover do início\n");
        printf("4. Remover do final\n");
        printf("5. Remover por chave\n");
        printf("6. Buscar por chave\n");
        printf("7. Imprimir lista\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor para inserir no início: ");
            scanf("%d", &valor);
            inserirInicio(lista, valor);
            break;
        case 2:
            printf("Digite o valor para inserir no final: ");
            scanf("%d", &valor);
            insereFinal(lista, valor);
            break;
        case 3:
            removeInicio(lista);
            printf("Removido do início.\n");
            break;
        case 4:
            removeFinal(lista);
            printf("Removido do final.\n");
            break;
        case 5:
            printf("Digite o valor da chave a ser removida: ");
            scanf("%d", &valor);
            removeChave(lista, valor);
            break;
        case 6:
            printf("Digite o valor da chave a ser buscada: ");
            scanf("%d", &valor);
            No *busca = buscaChave(lista, valor);
            if (busca != NULL)
                printf("Chave %d encontrada na lista.\n", valor);
            else
                printf("Chave %d não encontrada.\n", valor);
            break;
        case 7:
            printf("Lista: ");
            ImprimeLista(lista);
            break;
        case 8:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    }

    return 0;
}
