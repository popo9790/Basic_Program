#include <stdio.h>
#include <string.h>

typedef long long int lli;

char s[50] = "OuQ";
lli len[51];

void init();
void solve(int k, lli l);

int main(void)
{
    int k;
    lli l, r;

    init();
    while (scanf("%d %lld %lld", &k, &l, &r) != EOF)
    {
        for (lli i = l; i <= r; ++i)
        {
            solve(k, i);
        }
        puts("");
    }
}

void init()
{
    len[1] = 3;
    for (int i = 2; i < 51; ++i)
    {
        len[i] = 2 * len[i - 1] + 3;
    }
}

void solve(int k, lli l)
{
    if (k == 1)
    {
        printf("%c", s[l]);
        return;
    }

    if (l == 0)
        printf("O");
    else if (l < len[k - 1] + 1)
        solve(k - 1, l - 1);
    else if (l == len[k - 1] + 1)
        printf("u");
    else if (l > len[k - 1] + 1 && l < 2 * len[k - 1] + 2)
        solve(k - 1, l - 2 - len[k - 1]);
    else
        printf("Q");

    return;
}