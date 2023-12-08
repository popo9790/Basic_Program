#include <stdio.h>
#include <string.h>

int number, h;
int DP[21][21][21][21][21][21];
int pieces[21];
int win = 0, lose = 0;

void tetris(int ti, int a, int b, int c, int d, int e);
int max(int a, int b);

int main(void)
{
    int n;

    scanf("%d", &n);
    while (n--)
    {

        scanf("%d %d", &number, &h);
        for (int i = 0; i < number; ++i)
        {
            scanf("%d", &pieces[i]);
        }
        memset(DP, 0, sizeof(DP));
        win = 0;
        lose = 0;

        tetris(0, 0, 0, 0, 0, 0);
        if (win)
        {
            puts("Win");
        }
        else
        {
            printf("Lose at %d\n", lose + 1);
        }
    }

    return 0;
}

void tetris(int ti, int a, int b, int c, int d, int e)
{
    if (win || DP[ti][a][b][c][d][e])
    {
        return;
    }

    if (ti >= number)
    {
        win = 1;
        return;
    }

    int tmp;

    DP[ti][a][b][c][d][e] = 1;
    if (pieces[ti] == 1)
    {
        if (a + 4 <= h)
            tetris(ti + 1, a + 4, b, c, d, e);
        if (b + 4 <= h)
            tetris(ti + 1, a, b + 4, c, d, e);
        if (c + 4 <= h)
            tetris(ti + 1, a, b, c + 4, d, e);
        if (d + 4 <= h)
            tetris(ti + 1, a, b, c, d + 4, e);
        if (e + 4 <= h)
            tetris(ti + 1, a, b, c, d, e + 4);

        // rotate
        tmp = max(max(a, b), max(c, d));
        if (tmp + 1 <= h)
            tetris(ti + 1, tmp + 1, tmp + 1, tmp + 1, tmp + 1, e);
        tmp = max(max(b, c), max(d, e));
        if (tmp + 1 <= h)
            tetris(ti + 1, a, tmp + 1, tmp + 1, tmp + 1, tmp + 1);
    }
    else if (pieces[ti] == 2)
    {
        tmp = max(a, b);
        if (tmp + 2 <= h)
            tetris(ti + 1, tmp + 2, tmp + 2, c, d, e);
        tmp = max(b, c);
        if (tmp + 2 <= h)
            tetris(ti + 1, a, tmp + 2, tmp + 2, d, e);
        tmp = max(c, d);
        if (tmp + 2 <= h)
            tetris(ti + 1, a, b, tmp + 2, tmp + 2, e);
        tmp = max(d, e);
        if (tmp + 2 <= h)
            tetris(ti + 1, a, b, c, tmp + 2, tmp + 2);
    }
    else if (pieces[ti] == 3)
    {
        tmp = max(max(a, b + 1), c);
        if (tmp + 2 <= h)
            tetris(ti + 1, tmp + 1, tmp + 2, tmp + 1, d, e);
        tmp = max(max(b, c + 1), d);
        if (tmp + 2 <= h)
            tetris(ti + 1, a, tmp + 1, tmp + 2, tmp + 1, e);
        tmp = max(max(c, d + 1), e);
        if (tmp + 2 <= h)
            tetris(ti + 1, a, b, tmp + 1, tmp + 2, tmp + 1);
    }
    else
    {
        tmp = max(max(a + 1, b + 1), c);
        if (tmp + 1 <= h)
            tetris(ti + 1, tmp, tmp + 1, tmp + 1, d, e);
        tmp = max(max(b + 1, c + 1), d);
        if (tmp + 1 <= h)
            tetris(ti + 1, a, tmp, tmp + 1, tmp + 1, e);
        tmp = max(max(c + 1, d + 1), e);
        if (tmp + 1 <= h)
            tetris(ti + 1, a, b, tmp, tmp + 1, tmp + 1);

        // rotate
        tmp = max(a, b + 1);
        if (tmp + 2 <= h)
            tetris(ti + 1, tmp + 2, tmp + 1, c, d, e);
        tmp = max(b, c + 1);
        if (tmp + 2 <= h)
            tetris(ti + 1, a, tmp + 2, tmp + 1, d, e);
        tmp = max(c, d + 1);
        if (tmp + 2 <= h)
            tetris(ti + 1, a, b, tmp + 2, tmp + 1, e);
        tmp = max(d, e + 1);
        if (tmp + 2 <= h)
            tetris(ti + 1, a, b, c, tmp + 2, tmp + 1);
    }

    if (!win)
    {
        lose = max(lose, ti);
    }
}

int max(int a, int b)
{
    return a > b ? a : b;
}