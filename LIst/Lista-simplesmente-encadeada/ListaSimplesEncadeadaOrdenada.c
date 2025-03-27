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

No *insere(No *L, int ch)
{
    No *novo = criaNo(ch);
    No *aux = L, *pred = NULL;
    if (L == NULL)
        return novo;
    while (aux != NULL && ch > aux->chave)
    {
        pred = aux;
        aux = aux->prox;
    }
    if (pred == NULL)
    {
        novo->prox = aux;
        L = novo;
    }
    else
    {
        novo->prox = aux;
        pred->prox = novo;
    }
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
        while (aux != NULL && ch > aux->chave)
        {
            pred = aux;
            aux = aux->prox;
        }
        if (aux != NULL && aux->chave == ch)
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
            if (aux->chave >= ch)
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

    while (opcao != 7)
    {
        printf("\nPainel - Lista Simplesmente Encadeada\n");
        printf("1. Inserir \n");
        printf("2. Remover do início\n");
        printf("3. Remover do final\n");
        printf("4. Remover por chave\n");
        printf("5. Buscar por chave\n");
        printf("6. Imprimir lista\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Digite o valor para inserir: ");
            scanf("%d", &valor);
            lista = insere(lista, valor);
            break;
        case 2:
            lista = removeInicio(lista);
            printf("Removido do início.\n");
            break;
        case 3:
            lista = removeFinal(lista);
            printf("Removido do final.\n");
            break;
        case 4:
            printf("Digite o valor da chave a ser removida: ");
            scanf("%d", &valor);
            lista = removeChave(lista, valor);
            printf("Chave %d removida.\n", valor);
            break;
        case 5:
            printf("Digite o valor da chave a ser buscada: ");
            scanf("%d", &valor);
            No *busca = buscaChave(lista, valor);
            if (busca != NULL)
                printf("Chave %d encontrada na lista.\n", valor);
            else
                printf("Chave %d não encontrada.\n", valor);
            break;
        case 6:
            printf("Lista: ");
            ImprimeLista(lista);
            break;
        case 7:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
    }

    return 0;
}
