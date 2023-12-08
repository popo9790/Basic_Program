#include <stdio.h>

void DFS(int x, int y, int step);

int Sx, Sy, Mx, My;
int r, c, minstep = -1;
int map[1000][1000], used[1000][1000],
    dir[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    scanf(" %d %d ", &r, &c);
    for (int i = 0, j = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            char c;
            scanf(" %c", &c);
            if (c == 'o' || c == '^')
            {
                map[i][j] = 1;
            }
            else if (c == '.')
            {
                map[i][j] = 0;
            }
            else if (c == 'S')
            {
                map[i][j] = 0;
                Sx = i;
                Sy = j;
            }
            else if (c == 'M')
            {
                map[i][j] = 0;
                Mx = i;
                My = j;
            }
        }
    }

    DFS(Sx, Sy, 0);
    printf("%d\n", minstep);

    return 0;
}

void DFS(int x, int y, int step)
{
    if (x == Mx && y == My) // M's x and M's y
    {
        if (minstep == -1)
        {
            minstep = step;
        }
        if (step < minstep)
        {
            minstep = step;
        }
    }
    else
    {
        for (int i = 0; i < 4; ++i)
        {
            int nx, ny; // NewX and NewY
            nx = x + dir[i][0];
            ny = y + dir[i][1];

            if (nx < 0 || nx >= r || ny < 0 || ny >= c)
            {
                continue;
            }
            else
            {
                if (map[nx][ny] == 1 || used[nx][ny] == 1)
                {
                    continue;
                }
            }

            used[nx][ny] = 1;
            DFS(nx, ny, step + 1);
            used[nx][ny] = 0;
        }
    }
}