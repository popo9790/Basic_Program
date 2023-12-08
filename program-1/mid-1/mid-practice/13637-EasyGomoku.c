#include <stdio.h>

int board[15][15];
int time, flag = 0;
int direction[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};

void find(int x, int y, int goma)
{
    int count = -1;
    for (int i = 0; i < 8; ++i)
    {
        int r = 0, c = 0;
        if (i % 2 == 0)
        {
            count = -1;
        }
        for (int j = 0; j < 5; ++j)
        {
            if (x + r >= 0 && x + r < 15 && y + c >= 0 && y + c < 15)
            {
                if (board[x + r][y + c] == goma)
                {
                    count++;
                }
                else
                {
                    break;
                }
            }
            r += direction[i][0];
            c += direction[i][1];
        }
        if (count >= 5)
        {
            flag = goma;
        }
    }
}

int main(void)
{
    int n;

    scanf(" %d", &n);
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 15; ++j)
        {
            board[i][j] = 0;
        }
    }

    for (time = 0; time < n; ++time)
    {
        int x, y, goma = time % 2 + 1;

        scanf(" %d %d", &x, &y);

        board[x - 1][y - 1] = goma;
        find(x - 1, y - 1, goma);

        if (flag != 0)
        {
            break;
        }
    }

    if (flag == 1)
    {
        printf("LSC wins at the %dth step.\n", time + 1);
    }
    else if (flag == 2)
    {
        printf("TSC wins at the %dth step.\n", time + 1);
    }
    else
    {
        printf("There's no winner.\n");
    }

    return 0;
}