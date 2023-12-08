#include <stdio.h>

void hanoi(char fr, char to, char bu, int n);

int main(void)
{
    int n;

    scanf(" %d", &n);
    hanoi('A', 'C', 'B', n);

    return 0;
}

void hanoi(char fr, char to, char bu, int n)
{
    if (n == 1)
    {
        printf("%d\n", n);
    }
    else
    {
        hanoi('A', 'B', 'C', n - 1);
        printf("%d\n", n);
        hanoi('B', 'C', 'A', n - 1);
    }
}