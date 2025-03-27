#include "ArvoreBinaria.h"

Node *CreateNode(int data)
{
    Node *newNode = (Node *)calloc(1, sizeof(Node));
    if (!newNode)
    {
        printf("Allocation error!!");
        exit(1);
    }
    newNode->data = data;
    return newNode;
}

Node *searchNode(Node *T, int data)
{
    if (!T)
        return NULL;
    if (T->data == data)
        return T;
    if (T->data < data)
        return searchNode(T->left, data);
    else
        return searchNode(T->right, data);
}

Node *insertNode(Node *T, int data)
{
    if (!T)
    {
        return CreateNode(data);
    }
    if (T->data == data)
    {
        printf("Existing data");
        return T;
    }
    if (T->data < data)
        T->left = insertNode(T->left, data);
    else
        T->right = insertNode(T->right, data);
    return T;
}

Node *sucessor(Node *X, Node **dadSuc)
{
    Node *aux = X;
    while (aux->left != NULL)
    {
        *(*dadSuc) = *aux;
        aux = aux->left;
    }
    return aux;
}

Node *removeNode(Node *T, int data)
{
    Node *aux = T;
    Node *dad = NULL;
    Node *suc = NULL;

    while (aux->data != data && aux != NULL)
    {
        dad = aux;
        if (aux->data < data)
            aux = aux->left;
        else
            aux = aux->right;
    }
    if (aux == NULL)
    {
        printf("Non-existent data!");
        return NULL;
    }

    if (aux->right == NULL && aux->left == NULL) // caso nó folha
    {
        if (dad != NULL)
        {

            if (dad->data > aux->data)
                dad->right = NULL;
            else
                dad->left = NULL;
        }
    }
    else if (dad == NULL) // caso nó raiz
    {
        if (aux->right == NULL)
        {
            aux->data = aux->left->data;
            dad = aux;
            aux = aux->left;
        }
        else
        {
            aux->data = aux->right->data;
            dad = aux;
            aux = aux->right;
        }
        dad->left = aux->left;
        dad->right = aux->right;
    }
    else
    {
        if (aux->right == NULL)
            dad->left = aux->left;
        else if (aux->left == NULL)
            dad->right = aux->right;
        else
        {
            suc = sucessor(aux->right, &dad);
            aux->data = suc->data;
            aux = suc;
        }
    }
    free(aux);
    return T;
}

void printTree(Node *T, int level)
{
    if (T != NULL)
    {
        printTree(T->right, level + 1);
        for (int i = 0; i < level; i++)
            printf("\t");
        printf("%d\n", T->data);
        printTree(T->left, level + 1);
    }
}
