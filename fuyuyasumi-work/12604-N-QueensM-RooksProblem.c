#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cnt = 0;
int n, m;
int range;
int position[10][2];

void dfs(int col, int numQ, int numR);
int check(int col, int row, int state);

int main(void)
{
    while (scanf("%d %d", &n, &m) != EOF)
    {
        cnt = 0;
        range = n + m;
        memset(position, -1, sizeof(position));

        dfs(0, 0, 0);
        printf("%d\n", cnt);
    }
}

void dfs(int col, int numQ, int numR)
{
    if (col == range)
    {
        cnt++;
        return;
    }

    for (int row = 0; row < range; ++row)
    {
        if (numQ < n)
        {
            if (check(col, row, 0))
            {
                position[col][0] = row;
                dfs(col + 1, numQ + 1, numR);
                position[col][0] = -1;
            }
        }

        if (numR < m)
        {
            if (check(col, row, 1))
            {
                position[col][1] = row;
                dfs(col + 1, numQ, numR + 1);
                position[col][1] = -1;
            }
        }
    }
}

int check(int col, int row, int state)
{
    int flag = 1;
    for (int i = 0; i < col; ++i)
    {
        if (position[i][0] != -1)
        {
            if (position[i][0] == row || abs(position[i][0] - row) == abs(i - col))
                flag = 0;
        }
        else
        {
            if (state == 0)
            {
                if (position[i][1] == row || abs(position[i][1] - row) == abs(i - col))
                    flag = 0;
            }
            else if (position[i][1] == row)
                flag = 0;
        }
    }
    return flag;
}