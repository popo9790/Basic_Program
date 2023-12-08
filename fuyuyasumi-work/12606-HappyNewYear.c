#include <stdio.h>
#include <stdlib.h>

int position[200000];
int n;

int compare(const void *a, const void *b);

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n + 1; ++i)
        scanf("%d", &position[i]);

    qsort(position, n + 1, sizeof(int), compare);
    printf("%d\n", 2 * abs(position[0] - position[n]));
}

int compare(const void *a, const void *b)
{
    int i = *(int *)a;
    int j = *(int *)b;
    return i - j;
}