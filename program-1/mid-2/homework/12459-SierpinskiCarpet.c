#include <stdio.h>

unsigned long long sum = 1;
int num;

void Carpet(int n);

int main(void)
{
    scanf("%d", &num);
    if (num == 0)
    {
        sum = 0;
    }
    Carpet(1);
    printf("%llu\n", sum);
}

void Carpet(int n)
{
    if (n < num)
    {
        for (int i = 0; i < 8; ++i)
        {
            sum += 1;
            Carpet(n + 1);
        }
    }
    else
    {
        return;
    }
}