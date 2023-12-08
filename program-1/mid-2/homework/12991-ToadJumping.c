#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long int lli;

int cost[17] = {0}, color[17] = {0};
int jumped[17] = {0}, route[10000];
int E = -1, J = -1, T, num;

void jump(int n, int step);

int main(void)
{
    int s;

    scanf(" %d %d %d ", &num, &s, &T);
    for (int i = 1; i <= num; ++i)
    {
        scanf("%d", &cost[i]);
    }
    for (int i = 1; i <= num; ++i)
    {
        scanf("%d", &color[i]);
    }

    route[0] = s;
    jump(s, 1);

    printf("%d %d\n", E, J);

    return 0;
}

void jump(int n, int step)
{
    if (n == T)
    {
        lli sum = 0;
        for (int i = 0; i < step - 1; ++i)
        {
            sum += abs(route[i] - route[i + 1]) * abs(cost[route[i]] - cost[route[i + 1]]);
        }
        if (sum > E)
        {
            E = sum;
            J = step - 1;
        }
        if (sum == E && step - 1 > J)
        {
            J = step - 1;
        }
    }
    else
    {
        for (int i = -1; i < 2; i += 2)
        {
            if (n + i >= 1 && n + i <= num)
            {
                if (jumped[n + i] == 0)
                {
                    jumped[n] = 1;
                    route[step] = n + i;
                    jump(n + i, step + 1);
                    jumped[n] = 0;
                }
            }
        }
        for (int i = 1; i <= num; ++i)
        {
            if (color[i] == color[n] && i != n)
            {
                if (jumped[i] == 0)
                {
                    jumped[n] = 1;
                    route[step] = i;
                    jump(i, step + 1);
                    jumped[n] = 0;
                }
            }
        }
    }
}