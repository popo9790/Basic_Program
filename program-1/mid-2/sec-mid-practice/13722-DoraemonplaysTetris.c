#include <stdio.h>
#include <string.h>

#define SIZE 21
#define n run
#define w r
#define p step

int run, r;
int step[SIZE];
int map[25][5];
int dp[SIZE][SIZE][SIZE][SIZE][SIZE][SIZE];

void DP_init();
int max(int x, int y);
int solve(int ti, int a, int b, int c, int d, int e);

int main(void)
{
    int t;

    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &run, &r);
        for (int i = 0; i < run; ++i)
        {
            scanf("%d", &step[i]);
        }

        DP_init();

        int ans = solve(0, 0, 0, 0, 0, 0);
        if (ans == run + 1)
        {
            printf("Win\n");
        }
        else
        {
            printf("Lose at %d\n", ans);
        }
    }

    return 0;
}

void DP_init()
{
    memset(dp, -1, sizeof(dp));
}

int max(int x, int y)
{
    return x > y ? x : y;
}

int solve(int ti, int a, int b, int c, int d, int e)
{
    if (dp[ti][a][b][c][d][e] != -1)
        return dp[ti][a][b][c][d][e];
    if (ti >= n)
        return dp[ti][a][b][c][d][e] = n + 1;
    int val = ti + 1, tmp;
    if (p[ti] == 1)
    {

        if (a + 4 <= w)
            val = max(val, solve(ti + 1, a + 4, b, c, d, e));
        if (b + 4 <= w)
            val = max(val, solve(ti + 1, a, b + 4, c, d, e));
        if (c + 4 <= w)
            val = max(val, solve(ti + 1, a, b, c + 4, d, e));
        if (d + 4 <= w)
            val = max(val, solve(ti + 1, a, b, c, d + 4, e));
        if (e + 4 <= w)
            val = max(val, solve(ti + 1, a, b, c, d, e + 4));

        tmp = max(max(a, b), max(c, d));
        if (tmp + 1 <= w)
            val = max(val, solve(ti + 1, tmp + 1, tmp + 1, tmp + 1, tmp + 1, e));
        tmp = max(max(b, c), max(d, e));
        if (tmp + 1 <= w)
            val = max(val, solve(ti + 1, a, tmp + 1, tmp + 1, tmp + 1, tmp + 1));
    }
    else if (p[ti] == 2)
    {

        tmp = max(a, b);
        if (tmp + 2 <= w)
            val = max(val, solve(ti + 1, tmp + 2, tmp + 2, c, d, e));
        tmp = max(b, c);
        if (tmp + 2 <= w)
            val = max(val, solve(ti + 1, a, tmp + 2, tmp + 2, d, e));
        tmp = max(c, d);
        if (tmp + 2 <= w)
            val = max(val, solve(ti + 1, a, b, tmp + 2, tmp + 2, e));
        tmp = max(d, e);
        if (tmp + 2 <= w)
            val = max(val, solve(ti + 1, a, b, c, tmp + 2, tmp + 2));
    }
    else if (p[ti] == 3)
    {

        tmp = max(max(a, b + 1), c);
        if (tmp + 2 <= w)
            val = max(val, solve(ti + 1, tmp + 1, tmp + 2, tmp + 1, d, e));
        tmp = max(max(b, c + 1), d);
        if (tmp + 2 <= w)
            val = max(val, solve(ti + 1, a, tmp + 1, tmp + 2, tmp + 1, e));
        tmp = max(max(c, d + 1), e);
        if (tmp + 2 <= w)
            val = max(val, solve(ti + 1, a, b, tmp + 1, tmp + 2, tmp + 1));
    }
    else
    {
        tmp = max(max(a + 1, b + 1), c);
        if (tmp + 1 <= w)
            val = max(val, solve(ti + 1, tmp, tmp + 1, tmp + 1, d, e));
        tmp = max(max(b + 1, c + 1), d);
        if (tmp + 1 <= w)
            val = max(val, solve(ti + 1, a, tmp, tmp + 1, tmp + 1, e));
        tmp = max(max(c + 1, d + 1), e);
        if (tmp + 1 <= w)
            val = max(val, solve(ti + 1, a, b, tmp, tmp + 1, tmp + 1));

        tmp = max(a, b + 1);
        if (tmp + 2 <= w)
            val = max(val, solve(ti + 1, tmp + 2, tmp + 1, c, d, e));
        tmp = max(b, c + 1);
        if (tmp + 2 <= w)
            val = max(val, solve(ti + 1, a, tmp + 2, tmp + 1, d, e));
        tmp = max(c, d + 1);
        if (tmp + 2 <= w)
            val = max(val, solve(ti + 1, a, b, tmp + 2, tmp + 1, e));
        tmp = max(d, e + 1);
        if (tmp + 2 <= w)
            val = max(val, solve(ti + 1, a, b, c, tmp + 2, tmp + 1));
    }

    return dp[ti][a][b][c][d][e] = val;
}