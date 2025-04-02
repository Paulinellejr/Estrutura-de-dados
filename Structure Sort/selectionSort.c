#include <stdio.h>
#include <stdlib.h>
#define SIZE 11

int findSmallest(int *arr, int i)
{
    int smallest = arr[i];
    int smallestIndex = i;
    for (int j = i + 1; j < SIZE; j++)
    {
        if (arr[j] < smallest)
        {
            smallest = arr[j];
            smallestIndex = j;
        }
    }
    return smallestIndex;
}

void selectionSort(int *arr)
{
    for (int i = 0; i < SIZE - 1; i++)
    {
        int smallestIndex = findSmallest(arr, i);
        if (smallestIndex != i)
        {
            int temp = arr[i];
            arr[i] = arr[smallestIndex];
            arr[smallestIndex] = temp;
        }
    }
}

void printArray(int *arr)
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[SIZE] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    printf("Original array:\n");
    printArray(arr);

    selectionSort(arr);

    printf("Sorted array:\n");
    printArray(arr);

    return 0;
}
