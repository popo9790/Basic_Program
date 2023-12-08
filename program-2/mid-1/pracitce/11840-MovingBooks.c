#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
int map[25][25];
int len[25];
int pos[25];

void init();
void reBooks(int target);
void putOn(int from, int to);
void pileOn(int from, int to);
void Show();

int main(void)
{
    scanf("%d", &n);
    init();
    while (1)
    {
        int a, b;
        char str1[10], str2[10];
        scanf("%s", str1);
        if (!strcmp(str1, "exit"))
            break;
        scanf(" %d %s %d", &a, str2, &b);
        if (!(a == b || pos[a] == pos[b]))
        {
            if (!strcmp(str1, "move"))
            {
                reBooks(a);
                if (!strcmp(str2, "onto"))
                    reBooks(b);
                putOn(a, b);
            }
            else
            {
                if (!strcmp(str2, "onto"))
                    reBooks(b);
                pileOn(a, b);
            }
        }
    }
    Show();
}

void init()
{
    memset(map, -1, sizeof(map));
    memset(len, 0, sizeof(len));
    for (int i = 0; i < n; ++i)
    {
        map[i][len[i]++] = i;
        pos[i] = i;
    }
}

void reBooks(int target)
{
    int tar_table = pos[target];
    int tar_len = len[tar_table];

    int flag = 0;
    for (int i = 0; i < tar_len; ++i)
    {
        if (map[tar_table][i] == target)
        {
            flag = 1;
            continue;
        }
        if (flag)
        {
            int tmp = map[tar_table][i];
            len[tar_table]--;

            map[tmp][len[tmp]++] = tmp;
            pos[tmp] = tmp;
        }
    }
}

void putOn(int from, int to)
{
    int fr_table = pos[from];
    int to_table = pos[to];

    len[fr_table]--;
    map[to_table][len[to_table]++] = from;
    pos[from] = to_table;
}

void pileOn(int from, int to)
{
    int fr_table = pos[from];
    int fr_len = len[fr_table];
    int to_table = pos[to];

    int flag = 0;
    for (int i = 0; i < fr_len; ++i)
    {
        if (map[fr_table][i] == from || flag)
        {
            flag = 1;
            int tmp = map[fr_table][i];
            len[fr_table]--;

            map[to_table][len[to_table]++] = tmp;
            pos[tmp] = to_table;
        }
    }
}

void Show()
{
    for (int i = 0; i < n; ++i)
    {
        printf("%d:", i);
        if (len[i] != 0)
            for (int j = 0; j < len[i]; ++j)
                printf(" %d", map[i][j]);
        puts("");
    }
}