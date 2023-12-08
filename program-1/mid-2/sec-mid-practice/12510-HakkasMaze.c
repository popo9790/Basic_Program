#include <stdio.h>
#include <stdlib.h>

void DFS(int x, int y);

int r, c;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

int used[1001][1001];
char map[1001][1001];
int Tadd[2][1000001];

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    int n;

    scanf("%d", &n);
    while (n--)
    {
        scanf("%d %d ", &r, &c);

        for (int i = 0; i < r; ++i)
        {
            scanf("%s", map[i]);
        }

        for (int i = 0; i < r; ++i)
        {
            for (int j = 0; j < c; ++j)
            {
                used[i][j] = 0;
            }
        }

        int cur = 0;
        for (int i = 0; i < r; ++i)
        {
            for (int j = 0; j < c; ++j)
            {
                if (map[i][j] == 'T')
                {
                    Tadd[0][cur] = i;
                    Tadd[1][cur] = j;
                    cur++;
                }
            }
        }
        Tadd[0][cur] = -1;

        if (map[r - 1][c - 1] != '#')
        {
            used[r - 1][c - 1] = 1;
            DFS(r - 1, c - 1);
        }

        if (used[0][0])
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }

    return 0;
}

void DFS(int x, int y)
{
    if (used[0][0] == 1)
    {
        return;
    }

    if (map[x][y] == 'T')
    {
        for (int i = 0;; ++i)
        {
            if (Tadd[0][i] == -1)
            {
                break;
            }

            if (used[Tadd[0][i]][Tadd[1][i]] == 0)
            {
                used[Tadd[0][i]][Tadd[1][i]] = 1;
                DFS(Tadd[0][i], Tadd[1][i]);
            }
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        int nx, ny;

        nx = x + dir[i][0];
        ny = y + dir[i][1];

        if (nx >= 0 && nx < r && ny >= 0 && ny < c)
        {
            if (map[nx][ny] != '#' && used[nx][ny] == 0)
            {
                used[nx][ny] = 1;
                DFS(nx, ny);
            }
        }
    }
}