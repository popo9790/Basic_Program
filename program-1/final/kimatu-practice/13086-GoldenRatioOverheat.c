#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_Len 2001
typedef long long int lli;

char F0[Max_Len];
char F1[Max_Len];
lli len[60];

void init();
char battle(int n, lli k);

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        lli k;

        scanf(" %s %s ", F0, F1);
        len[0] = strlen(F0);
        len[1] = strlen(F1);
        init();

        scanf("%d %lld", &n, &k);
        char ans = battle(n, k);

        printf("%c\n", ans);
    }
}

void init()
{
    for (int i = 2; i < 60; ++i)
    {
        len[i] = len[i - 2] + len[i - 1];
    }
}

char battle(int n, lli k)
{
    if (n == 0)
    {
        return F0[k];
    }
    if (n == 1)
    {
        return F1[k];
    }

    if (k < len[n - 2])
    {
        return battle(n - 2, k);
    }
    else
    {
        return battle(n - 1, k - len[n - 2]);
    }
}
