#include <stdio.h>
#include <string.h>

int l, r, k;
char s[10001];

void strshift(int k);

int main(void)
{
    int m;
    scanf("%s", s);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i)
    {
        scanf("%d %d %d", &l, &r, &k);
        strshift(k);
    }
    puts(s);
}

void strshift(int k)
{
    int dis = r - l + 1;
    int t = k % (dis);
    char buff[dis + 1];

    if (t != 0)
    {
        strncpy(buff, s + l - 1, dis);
        for (int i = l - 1, j = 0; i < r; ++i, ++j)
            s[i] = buff[(dis - t + j) % dis];
        // (dis - t) represents where it starts
        // +j control the iterator
    }
}