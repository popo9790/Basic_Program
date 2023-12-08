#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int DirX[] = {1, 1, -1, -1, 2, 2, -2, -2};
int DirY[] = {2, -2, 2, -2, 1, -1, 1, -1};

int n;
int flag = 0;
char map[105][105];
char ans[] = "ICPCASIASG";

void solve(int state, int x, int y);

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            scanf(" %c ", &map[i][j]);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (map[i][j] == 'I')
                solve(1, i, j);

    if (flag)
        puts("YES");
    else
        puts("NO");
}

void solve(int state, int x, int y)
{
    if (flag)
        return;

    if (state == strlen(ans))
    {
        flag = 1;
        return;
    }

    for (int i = 0; i < 8; ++i)
    {
        int nx = x + DirX[i];
        int ny = y + DirY[i];

        if (nx >= 0 && nx < n && ny >= 0 && ny < n)
            if (map[nx][ny] == ans[state])
                solve(state + 1, nx, ny);
    }
}
