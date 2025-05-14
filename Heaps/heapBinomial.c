#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

typedef struct bnode
{
    int key;
    int degree;
    struct bnode *parent;
    struct bnode *child;
    struct bnode *sibling;
} Bnode;

typedef struct heapB
{
    Bnode *head;
} HeapB;

// Cria um nó
Bnode *createNode(int key)
{
    Bnode *newNode = (Bnode *)calloc(1, sizeof(Bnode));
    if (!newNode)
    {
        printf("ERRO de Alocação!!\n");
        exit(1);
    }
    newNode->key = key;
    return newNode;
}

// Mescla duas árvores binomiais de mesmo grau
Bnode *mergeTrees(Bnode *T1, Bnode *T2)
{
    if (T1->key > T2->key)
    {
        Bnode *aux = T1;
        T1 = T2;
        T2 = aux;
    }
    T2->parent = T1;
    T2->sibling = T1->child;
    T1->child = T2;
    T1->degree++;
    return T1;
}

// Mescla duas heaps binomiais
HeapB *mergeHeaps(HeapB *h1, HeapB *h2)
{
    if (!h1->head)
        return h2;
    if (!h2->head)
        return h1;

    HeapB *h3 = (HeapB *)malloc(sizeof(HeapB));
    h3->head = NULL;

    Bnode *prev = NULL;
    Bnode *current = NULL;
    Bnode *next = NULL;

    // Passo 1: Unir as listas de árvores ordenadas por grau
    Bnode *h1Node = h1->head;
    Bnode *h2Node = h2->head;
    if (h1Node->degree <= h2Node->degree)
    {
        h3->head = h1Node;
        h1Node = h1Node->sibling;
    }
    else
    {
        h3->head = h2Node;
        h2Node = h2Node->sibling;
    }
    current = h3->head;

    while (h1Node && h2Node)
    {
        if (h1Node->degree <= h2Node->degree)
        {
            current->sibling = h1Node;
            h1Node = h1Node->sibling;
        }
        else
        {
            current->sibling = h2Node;
            h2Node = h2Node->sibling;
        }
        current = current->sibling;
    }

    if (h1Node)
        current->sibling = h1Node;
    if (h2Node)
        current->sibling = h2Node;

    // Passo 2: Ajustar árvores de mesmo grau
    prev = NULL;
    current = h3->head;
    next = current->sibling;

    while (next)
    {
        if ((current->degree != next->degree) ||
            (next->sibling && next->sibling->degree == current->degree))
        {
            prev = current;
            current = next;
        }
        else
        {
            if (current->key <= next->key)
            {
                current->sibling = next->sibling;
                mergeTrees(current, next);
            }
            else
            {
                if (!prev)
                    h3->head = next;
                else
                    prev->sibling = next;
                mergeTrees(next, current);
                current = next;
            }
        }
        next = current->sibling;
    }
    return h3;
}

// Encontra o menor nó da heap
Bnode *findMin(HeapB *H)
{
    Bnode *minNode = H->head;
    Bnode *current = H->head;
    int minValue = INT_MAX;

    while (current)
    {
        if (current->key < minValue)
        {
            minValue = current->key;
            minNode = current;
        }
        current = current->sibling;
    }
    return minNode;
}

// Insere um nó na heap
void insertNode(HeapB **H, int key)
{
    HeapB *tempHeap = (HeapB *)malloc(sizeof(HeapB));
    tempHeap->head = createNode(key);
    *H = mergeHeaps(*H, tempHeap);
}

// Extrai o nó mínimo da heap
Bnode *extractMin(HeapB **H)
{
    if (!(*H)->head)
        return NULL;

    Bnode *minNode = findMin(*H);
    Bnode *current = (*H)->head;
    Bnode *prev = NULL;

    while (current && current != minNode)
    {
        prev = current;
        current = current->sibling;
    }

    if (prev)
        prev->sibling = current->sibling;
    else
        (*H)->head = current->sibling;

    // Inverte a lista de filhos do nó removido
    Bnode *child = minNode->child;
    Bnode *reversedChild = NULL;
    while (child)
    {
        Bnode *next = child->sibling;
        child->sibling = reversedChild;
        child->parent = NULL;
        reversedChild = child;
        child = next;
    }

    HeapB *tempHeap = (HeapB *)malloc(sizeof(HeapB));
    tempHeap->head = reversedChild;
    *H = mergeHeaps(*H, tempHeap);

    return minNode;
}

// Exibe a heap binomial
void printHeap(HeapB *H)
{
    Bnode *current = H->head;
    while (current)
    {
        printf("B%d: ", current->degree);
        Bnode *temp = current;
        while (temp)
        {
            printf("%d, ", temp->key);
            temp = temp->child;
        }
        printf("\n");
        current = current->sibling;
    }
}

int main()
{
    HeapB *H = (HeapB *)malloc(sizeof(HeapB));
    H->head = NULL;

    insertNode(&H, 10);
    insertNode(&H, 20);
    insertNode(&H, 5);
    insertNode(&H, 15);
    insertNode(&H, 30);

    printf("Heap Binomial após inserções:\n");
    printHeap(H);

    Bnode *minNode = extractMin(&H);
    if (minNode)
    {
        printf("\nMínimo removido: %d\n", minNode->key);
        free(minNode);
    }

    printf("Heap Binomial após remoção do mínimo:\n");
    printHeap(H);

    return 0;
}
