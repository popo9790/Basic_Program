#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void IterateAll();
void find(int x, int y, char goma);

char map[16][16], win = '0', check = '0';
int ligal = 1;
int direction[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}};

int main(void)
{
    int t;

    scanf("%d", &t);
    while (t--)
    {
        int b = 0, w = 0, flag = 1;

        for (int i = 0; i < 15; ++i)
        {
            scanf(" %s", map[i]);
        }

        for (int i = 0; i < 15; ++i)
        {
            for (int j = 0; j < 15; ++j)
            {
                if (map[i][j] == '1')
                {
                    b++;
                }
                else if (map[i][j] == '2')
                {
                    w++;
                }
            }
        }

        if (b - w > 1)
        {
            printf("No\n");
        }
        else
        {
            if (b > w)
            {
                check = '1';
            }
            else
            {
                check = '0';
            }

            for (int i = 0; i < 15; ++i)
            {
                for (int j = 0; j < 15; ++j)
                {
                    if (map[i][j] == '1')
                    {
                        find(i, j, '1');
                    }
                    else if (map[i][j] == '2')
                    {
                        find(i, j, '1');
                    }
                }
            }

            if ((check != win && win != '0'))
            {
                ligal = 0;
            }

            if (ligal)
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
        }

        check = '0';
        win = '0';
        ligal = 1;
    }

    return 0;
}

void find(int x, int y, char goma)
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
                if (map[x + r][y + c] == goma)
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
        if (count == 5)
        {
            if (win == '0' || win == goma)
            {
                win = goma;
            }
            else
            {
                ligal = 0;
                break;
            }
        }
    }
}

void IterateAll()
{
    if (win != '0')
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; ++j)
            {
                if (map[i][j] == win)
                {
                    map[i][j] = '0';
                    find(i, j, win);
                    map[i][j] = win;
                }
            }
        }
    }
}