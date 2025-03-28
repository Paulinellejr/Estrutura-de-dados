#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef struct FibNode
{
    struct FibNode *parent;
    struct FibNode *child;
    struct FibNode *left;
    struct FibNode *right;
    int key;
    int degree;
    int mark;
} FibNode;

typedef struct HeapF
{
    FibNode *min;
    int n;
} HeapF;

FibNode *createNode(int key)
{
    FibNode *newNode = (FibNode *)malloc(sizeof(FibNode));
    if (!newNode)
    {
        printf("ERROR allocating memory\n");
        exit(1);
    }
    newNode->key = key;
    newNode->right = newNode;
    newNode->left = newNode;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->degree = 0;
    newNode->mark = 0;
    return newNode;
}

HeapF *createHeap()
{
    HeapF *H = (HeapF *)malloc(sizeof(HeapF));
    if (!H)
    {
        printf("ERROR allocating memory\n");
        exit(1);
    }
    H->min = NULL;
    H->n = 0;
    return H;
}

FibNode *minimum(HeapF *H)
{
    return H->min;
}

void insert(HeapF *H, int key)
{
    FibNode *newNode = createNode(key);
    if (H->min == NULL)
    {
        H->min = newNode;
    }
    else
    {
        newNode->right = H->min;
        newNode->left = H->min->left;
        H->min->left->right = newNode;
        H->min->left = newNode;
        if (key < H->min->key)
        {
            H->min = newNode;
        }
    }
    H->n++;
}

HeapF *unionHeaps(HeapF *H1, HeapF *H2)
{
    if (!H1->min)
        return H2;
    if (!H2->min)
        return H1;

    FibNode *leftH1 = H1->min->left;
    FibNode *leftH2 = H2->min->left;

    leftH1->right = H2->min;
    H2->min->left = leftH1;
    leftH2->right = H1->min;
    H1->min->left = leftH2;

    if (H2->min->key < H1->min->key)
    {
        H1->min = H2->min;
    }

    H1->n += H2->n;
    free(H2);
    return H1;
}

void consolidate(HeapF *H)
{
    if (H->min == NULL)
        return;

    int maxDegree = (int)(log2(H->n)) + 1;
    FibNode *A[maxDegree];
    for (int i = 0; i < maxDegree; i++)
        A[i] = NULL;

    FibNode *current = H->min;
    FibNode *start = current;

    do
    {
        FibNode *x = current;
        int degree = x->degree;
        current = current->right;

        while (A[degree] != NULL)
        {
            FibNode *y = A[degree];
            if (x->key > y->key)
            {
                FibNode *temp = x;
                x = y;
                y = temp;
            }

            if (y == H->min)
            {
                H->min = x;
            }
            y->left->right = y->right;
            y->right->left = y->left;
            if (x->child == NULL)
            {
                x->child = y;
            }
            else
            {
                y->left = x->child->left;
                x->child->left->right = y;
                x->child->left = y;
            }
            y->parent = x;
            x->degree++;
            A[degree] = NULL;
            degree++;
        }
        A[degree] = x;
    } while (current != start);

    H->min = NULL;
    for (int i = 0; i < maxDegree; i++)
    {
        if (A[i] != NULL)
        {
            if (H->min == NULL || A[i]->key < H->min->key)
            {
                H->min = A[i];
            }
        }
    }
}

FibNode *extractMin(HeapF *H)
{
    FibNode *min = H->min;
    if (!min)
        return NULL;

    if (min->child != NULL)
    {
        FibNode *child = min->child;
        do
        {
            FibNode *next = child->right;
            child->parent = NULL;

            child->right = H->min;
            child->left = H->min->left;
            H->min->left->right = child;
            H->min->left = child;

            child = next;
        } while (child != min->child);
    }

    min->left->right = min->right;
    min->right->left = min->left;

    if (min == min->right)
    {
        H->min = NULL;
    }
    else
    {
        H->min = min->right;
        consolidate(H);
    }

    H->n--;
    return min;
}

void cut(HeapF *H, FibNode *x, FibNode *y)
{
    if (x->right == x)
    {
        y->child = NULL;
    }
    else
    {
        x->left->right = x->right;
        x->right->left = x->left;
        if (y->child == x)
        {
            y->child = x->right;
        }
    }
    y->degree--;

    x->parent = NULL;
    x->mark = 0;

    x->right = H->min;
    x->left = H->min->left;
    H->min->left->right = x;
    H->min->left = x;

    if (x->key < H->min->key)
    {
        H->min = x;
    }
}

void cascadingCut(HeapF *H, FibNode *y)
{
    FibNode *z = y->parent;
    if (z != NULL)
    {
        if (y->mark == 0)
        {
            y->mark = 1;
        }
        else
        {
            cut(H, y, z);
            cascadingCut(H, z);
        }
    }
}

void decreaseKey(HeapF *H, FibNode *x, int k)
{
    FibNode *y;
    if (k > x->key)
    {
        printf("ERROR: New key is greater than current key!\n");
        return;
    }
    x->key = k;
    y = x->parent;
    if (y != NULL && x->key < y->key)
    {
        cut(H, x, y);
        cascadingCut(H, y);
    }
    if (x->key < H->min->key)
    {
        H->min = x;
    }
}

void delete(HeapF *H, FibNode *x)
{
    decreaseKey(H, x, INT_MIN);
    FibNode *min = extractMin(H);
    free(min);
}

void freeNodes(FibNode *node)
{
    if (node != NULL)
    {
        FibNode *child = node->child;
        FibNode *next = node->right;
        freeNodes(child);
        free(node);
        freeNodes(next);
    }
}

void printRoots(HeapF *H)
{
    if (H->min == NULL)
    {
        printf("Heap is empty.\n");
        return;
    }

    FibNode *current = H->min;
    do
    {
        printf("%d ", current->key);
        current = current->right;
    } while (current != H->min);
    printf("\n");
}

int main()
{
    HeapF *H = createHeap();

    insert(H, 10);
    insert(H, 3);
    insert(H, 7);
    insert(H, 5);

    printf("Roots of the Heap after insertions: ");
    printRoots(H);

    FibNode *minNode = extractMin(H);
    if (minNode != NULL)
    {
        printf("Extracted minimum: %d\n", minNode->key);
        free(minNode);
    }

    printf("Roots of the Heap after extracting minimum: ");
    printRoots(H);

    freeNodes(H->min);
    free(H);

    return 0;
}
