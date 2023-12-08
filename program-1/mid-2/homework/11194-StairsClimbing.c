#include <stdio.h>

int step(int x);

int main(void)
{
    int n;

    scanf(" %d", &n);
    for (int i = 0; i < n; ++i)
    {
        int stairs;
        scanf("%d", &stairs);
        printf("%d\n", step(stairs));
    }

    return 0;
}

int step(int x)
{
    if (x == 1)
    {
        return 1;
    }
    if (x == 2)
    {
        return 2;
    }
    return step(x - 1) + step(x - 2);
}