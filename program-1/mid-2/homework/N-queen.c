#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int q[100], num, sum = 0;

void queen(int n);
void display();
int valid(int r, int c);

int main(void)
{
    memset(q, -1, sizeof(q));

    scanf("%d", &num);
    queen(0);

    return 0;
}

void queen(int n)
{
    if (n >= num)
    {
        printf("\n");
        display();

        return;
    }
    else
    {
        for (int j = 0; j < num; ++j)
        {
            if (valid(n, j))
            {
                q[n] = j;
                queen(n + 1);
            }
        }
    }
}

int valid(int r, int c)
{
    for (int i = 0; i < r; ++i)
    {
        if (q[i] == c || abs(i - r) == abs(q[i] - c))
        {
            return 0;
        }
    }

    return 1;
}

void display()
{
    for (int i = 0; i < num; ++i)
    {
        for (int j = 0; j < num; ++j)
        {
            if (q[i] == j)
            {
                printf("O%c", " \n"[j == num - 1]);
            }
            else
            {
                printf("X%c", " \n"[j == num - 1]);
            }
        }
    }
}