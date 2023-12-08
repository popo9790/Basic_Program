#include <stdio.h>
#define MAX 10
#define swap(a, b)    \
    if (a != b)       \
    {                 \
        (*a) ^= (*b); \
        (*b) ^= (*a); \
        (*a) ^= (*b); \
    }

void selection_sort(int *a, int size);
void Selection_SortRecursion(int *a, int size, int current);

int a[MAX] = {3, 7, 9, 1, 4, 0, 8, 6, 2, 5};

int main(void)
{
    Selection_SortRecursion(a, MAX, 0);
    // selection_sort(a, MAX);
    for (int i = 0; i < MAX; i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}

void selection_sort(int *a, int size)
{
    int i, j, min_idx;
    // Put the i-th smallest number in a[i].
    for (i = 0; i < size - 1; i++)
    {
        // Scan through the remaining array and pick the smallest element.
        min_idx = i;
        for (j = i + 1; j < size; j++)
        {
            if (a[min_idx] > a[j])
                min_idx = j;
        }
        // Swap the smallest number to the left.
        swap(&a[i], &a[min_idx]);
    }
}

void Selection_SortRecursion(int *a, int size, int current)
{
    int min = current;

    if (current == size)
    {
        return;
    }

    for (int i = current; i < size; ++i)
    {
        if (a[i] < a[min])
        {
            min = i;
        }
    }

    swap(&a[current], &a[min]);
    Selection_SortRecursion(a, size, current + 1);
}
