#include <stdio.h>
#include <string.h>

int size;
int main(void)
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {

        scanf(" %d", &size);

        int map[size][size];
        for (int x = 0; x < size; ++x)
        {
            for (int y = 0; y < size; ++y)
            {
                map[x][y] = ' ';
            }
        }

        for (int t = 0, x = 0, y = 0; t < size; ++t)
        {
            int tmp;
            switch (t % 4)
            {
            case 0:
                for (int j = 0; j < size - t; ++j)
                {
                    map[x][y + j] = '#';
                    tmp = y + j;
                }
                x++;
                y = tmp;
                break;
            case 1:
                for (int j = 0; j < size - t; ++j)
                {
                    map[x + j][y] = '#';
                    tmp = x + j;
                }
                y--;
                x = tmp;
                break;
            case 2:
                for (int j = 0; j < size - t; ++j)
                {
                    map[x][y - j] = '#';
                    tmp = y - j;
                }
                x--;
                y = tmp;
                break;
            case 3:
                for (int j = 0; j < size - t; ++j)
                {
                    map[x - j][y] = '#';
                    tmp = x - j;
                }
                y++;
                x = tmp;
                break;
            }
        }

        for (int x = 0; x < size; ++x)
        {
            for (int y = 0; y < size; ++y)
            {
                printf("%c", map[x][y]);
            }
            printf("\n");
        }
    }
    return 0;
}