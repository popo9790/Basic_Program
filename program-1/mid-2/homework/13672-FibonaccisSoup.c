#include <stdio.h>

long DFSf(int x);
long DFSg(int x);
int a, b, c, d;

int main(void)
{
    int n;

    scanf(" %d %d %d %d %d", &a, &b, &c, &d, &n);

    printf("%ld %ld\n", DFSf(n), DFSg(n));

    return 0;
}

long DFSf(int x)
{
    if (x == 0)
    {
        return a;
    }
    else if (x == 1)
    {
        return b;
    }
    else if (x % 2 == 0)
    {
        return DFSf(x - 1) + DFSg(x / 2);
    }
    else
    {
        return DFSf(x - 1) + DFSg(x - 2);
    }
}

long DFSg(int x)
{
    if (x == 0)
    {
        return c;
    }
    else if (x == 1)
    {
        return d;
    }
    else if (x % 3 == 0)
    {
        return DFSg(x - 1) + DFSf(x / 3);
    }
    else
    {
        return DFSg(x - 1) + DFSf(x - 2);
    }
}