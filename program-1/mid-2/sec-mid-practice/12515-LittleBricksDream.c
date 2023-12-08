#include <stdio.h>
#include <stdlib.h>

int n, x;
int dp[10000000];
int ans[10000000];

int check(int cur, int *line);
void f(int cur, int *line, int index);

int main(void)
{
    int *line;

    scanf("%d %d", &n, &x);
    line = (int *)(malloc(n * sizeof(int)));

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &line[i]);
        dp[i] = -1;
    }

    ans[0] = -1;
    f(1, line, 0);

    if (ans[0] == -1)
    {
        printf("ouo\n");
    }
    else
    {
        printf("%d", ans[0]);
        for (int i = 1;; ++i)
        {
            if (ans[i] == -1)
            {
                puts("");
                break;
            }
            else
            {
                printf(" %d", ans[i]);
            }
        }
    }

    free(line);

    return 0;
}

void f(int cur, int *line, int index)
{
    if (cur == n)
    {
        ans[index] = -1;
        return;
    }

    if (line[cur] > line[cur - 1])
    {
        if (dp[cur - 1] == -1)
        {
            dp[cur] = check(cur, line);
        }
        else
        {
            dp[cur] = dp[cur - 1] + 1;
        }

        if (dp[cur] == x)
        {
            ans[index] = cur + 1;
            index++;
        }
    }

    f(cur + 1, line, index);
}

int check(int cur, int *line)
{
    int sum = 0;
    for (int i = cur - 1; i >= 0; --i)
    {
        if (line[cur] > line[i])
        {
            sum++;
        }
        else
        {
            break;
        }
    }

    return sum;
}