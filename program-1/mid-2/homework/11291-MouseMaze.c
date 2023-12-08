#include <stdio.h>
#include <string.h>

typedef long long int lli;

int r, c;
int Sx, Sy, Fx, Fy;
lli lstep = __LONG_LONG_MAX__;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

int used[501][501];
char maze[500 + 1][500 + 1];

void CheckPt();
void Mouse(int x, int y, int step);

int main(void)
{
    int t;

    scanf("%d", &t);
    while (t--)
    {
        scanf(" %d %d ", &r, &c);
        for (int i = 0; i < r; ++i)
        {
            scanf("%s", maze[i]);
        }
        maze[r][c] = '\0';

        CheckPt();
        used[Sx][Sy] = 1;
        Mouse(Sx, Sy, 0);

        if (lstep == __LONG_LONG_MAX__)
        {
            lstep = -1;
        }

        printf("%d\n", lstep);
        lstep = __LONG_LONG_MAX__;
    }

    return 0;
}

void CheckPt()
{
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            if (maze[i][j] == 'S')
            {
                Sx = i;
                Sy = j;
            }
            if (maze[i][j] == 'F')
            {
                Fx = i;
                Fy = j;
            }
        }
    }
}

void Mouse(int x, int y, int step)
{
    if (maze[x][y] == 'F')
    {
        if (step < lstep)
        {
            lstep = step;
        }
    }
    else
    {
        if (step > lstep)
        {
            return;
        }

        int Nx = x;
        int Ny = y;
        for (int i = 0; i < 4; ++i)
        {
            Nx = x + dir[i][0];
            Ny = y + dir[i][1];

            if (Nx >= 0 && Nx < r && Ny >= 0 && Ny < c && used[Nx][Ny] == 0)
            {
                if (maze[Nx][Ny] != '#')
                {
                    used[x][y] = 1;
                    Mouse(Nx, Ny, step + 1);
                    used[x][y] = 0;
                }
            }
        }
    }
}