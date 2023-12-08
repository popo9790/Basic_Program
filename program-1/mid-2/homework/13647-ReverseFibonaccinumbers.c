#include <stdio.h>

int a, b;
long long ReFabo(int x);

int main(void)
{
    int n;
    scanf("%d %d %d", &a, &b, &n);

    printf("%lld\n", ReFabo(n));
    return 0;
}

long long ReFabo(int n)
{
    if (n == 0)
    {
        return a;
    }
    if (n == 1)
    {
        return b;
    }
    return ReFabo(n - 2) - ReFabo(n - 1);
}