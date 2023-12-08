#include <stdio.h>

int cost[1000];
int money[1000];

int main(void)
{
    int n, m;
    int cnt = 0;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i)
        scanf("%d", &cost[i]);
    for (int i = 0; i < m; ++i)
        scanf("%d", &money[i]);

    for (int i = 0, j = 0;;)
    {
        if (i == n || j == m)
            break;

        if (money[j] >= cost[i])
        {
            i++;
            j++;
            cnt++;
        }
        else
            i++;
    }

    printf("%d\n", cnt);
}