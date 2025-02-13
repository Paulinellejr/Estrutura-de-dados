#ifndef __ARVOREBINARIA_H__
#define __ARVOREBINARIA_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *right;
    struct node *left;
} Node;

Node *CreateNode(int id);

Node *searchNode(Node *T, int data);
Node *insertNode(Node *T, int data);
Node *removeNode(Node *T, int data);
Node *sucessor(Node *X, Node **dadSuc);
void printTree(Node *T, int level);
#endif
