#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, m;
int len[100];
char *sud[100];

void init();
void add(int x, char *s);
void _delete(int x, int k);
void swap(int x, int y);
void longest();
void all();

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    scanf("%d %d", &n, &m);
    init();
    while (m--)
    {
        char op[7];
        scanf("%s", op);
        if (strcmp(op, "add") == 0)
        {
            int x;
            char s[101];
            scanf("%d %s", &x, s);
            add(x - 1, s);
        }
        else if (strcmp(op, "delete") == 0)
        {
            int x, k;
            scanf("%d %d", &x, &k);
            _delete(x - 1, k);
        }
        else if (strcmp(op, "swap") == 0)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            swap(x - 1, y - 1);
        }
        else if (strcmp(op, "longest") == 0)
        {
            longest();
        }
        else if (strcmp(op, "all") == 0)
        {
            all();
        }
    }

    for (int i = 0; i < n; ++i)
    {
        free(sud[i]);
    }
}

void init()
{
    for (int i = 0; i < n; ++i)
    {
        len[i] = 0;
        sud[i] = (char *)malloc(sizeof(char));
        sud[i][0] = '\0';
    }
}

void add(int x, char *s)
{
    char *tmp = (char *)malloc((len[x] + 1) * sizeof(char));
    strcpy(tmp, sud[x]);
    free(sud[x]);
    len[x] += strlen(s);

    sud[x] = (char *)malloc((len[x] + 1) * sizeof(char));
    strcpy(sud[x], tmp);
    strcat(sud[x], s);
    free(tmp);
}

void _delete(int x, int k)
{
    if (k > len[x])
    {
        len[x] = 0;
        free(sud[x]);
        sud[x] = (char *)malloc(sizeof(char));
        sud[x][0] = '\0';
    }
    else
    {
        len[x] -= k;
        char *tmp = (char *)malloc((len[x] + 1) * sizeof(char));
        strncpy(tmp, sud[x], len[x]);
        tmp[len[x]] = '\0';
        free(sud[x]);
        sud[x] = tmp;
    }
}

void longest()
{
    int max = len[0];
    int maxin = 0;
    for (int i = 0; i < n; ++i)
    {
        if (len[i] > max)
        {
            max = len[i];
            maxin = i;
        }
    }
    printf("%d %s\n", max, sud[maxin]);
}

void swap(int x, int y)
{
    char *tmpc;
    tmpc = sud[x];
    sud[x] = sud[y];
    sud[y] = tmpc;

    int tmpi;
    tmpi = len[x];
    len[x] = len[y];
    len[y] = tmpi;
}

void all()
{
    for (int i = 0; i < n; ++i)
    {
        printf("%s\n", sud[i]);
    }
}