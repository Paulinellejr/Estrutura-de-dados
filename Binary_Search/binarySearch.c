#include <stdio.h>
#include <stdlib.h>

int binarySearch(int *list, int size, int item)
{
    int low = 0;
    int high = size - 1;
    int half;

    while (low <= high)
    {
        half = (low + high) / 2;
        int shot = list[half];

        if (shot == item)
            return half;
        else if (shot > item)
            high = half - 1;
        else
            low = half + 1;
    }

    return -1;
}

int main()
{
    int list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(list) / sizeof(list[0]);
    int item = 4;

    int index = binarySearch(list, size, item);

    if (index != -1)
        printf("Item %d found at index %d.\n", item, index);
    else
        printf("Item %d not found.\n", item);

    return 0;
}
