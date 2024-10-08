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
        printf("Erro de alocação");
        exit(1);
    }
    novo->chave = ch;
    novo->prox = NULL;
    return novo;
}

No *insereinicio(No *L, int ch)
{
    No *novo = criaNo(ch);
    novo->prox = L;
    return novo;
}

No *insereFinal(No *L, int ch)
{
    No *novo = criaNo(ch);
    No *aux = L;
    if (L == NULL)
        return novo;
    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    aux->prox = novo;
    return L;
}

No *removeInicio(No *L)
{
    No *aux = L;
    if (L == NULL)
        return NULL;
    else
    {
        L = L->prox;
        free(aux);
        return L;
    }
}
No *removeFinal(No *L)
{
    No *pred = NULL;
    No *aux = L;
    if (L == NULL)
        return NULL;
    else
    {
        while (aux->prox != NULL)
        {
            pred = aux;
            aux = aux->prox;
        }
        if (pred == NULL)
            L = NULL;
        else
            pred->prox = NULL;
        free(aux);
        return L;
    }
}
No *removeChave(No *L, int ch)
{
    No *aux = L;
    No *pred = NULL;
    if (L == NULL)
        return NULL;
    else
    {
        while (aux != NULL && ch != aux->chave)
        {
            pred = aux;
            aux = aux->prox;
        }
        if (aux != NULL)
        {
            if (pred == NULL)
                L = aux->prox;
            else
                pred->prox = aux->prox;
            free(aux);
        }
        return L;
    }
}
No *buscaChave(No *L, int ch)
{
    No *aux = L;
    if (L == NULL)
        return NULL;
    else
    {

        while (aux != NULL)
        {
            if (aux->chave == ch)
                break;
            aux = aux->prox;
        }
        return aux;
    }
}

void ImprimeLista(No *L)
{
    No *aux = L;
    if (L == NULL)
    {
        printf("Lista vazia!");
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
    No *lista = NULL;
    int opcao, valor;

    while (opcao != 8)
    {
        printf("\nPainel - Lista Simplesmente Encadeada\n");
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
            lista = insereinicio(lista, valor);
            break;
        case 2:
            printf("Digite o valor para inserir no final: ");
            scanf("%d", &valor);
            lista = insereFinal(lista, valor);
            break;
        case 3:
            lista = removeInicio(lista);
            printf("Removido do início.\n");
            break;
        case 4:
            lista = removeFinal(lista);
            printf("Removido do final.\n");
            break;
        case 5:
            printf("Digite o valor da chave a ser removida: ");
            scanf("%d", &valor);
            lista = removeChave(lista, valor);
            printf("Chave %d removida.\n", valor);
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