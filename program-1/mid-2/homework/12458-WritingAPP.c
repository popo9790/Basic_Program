#include <stdio.h>
#include <string.h>

// Find the lenth of LCS and substract to original lengh

int k, n;
int DP[1001][1001];
char s1[1001], s2[1001];

int Palindrome(int x, int y);
int max(int a, int b);

int main(void)
{
    scanf(" %d %d ", &n, &k);
    scanf("%s", s1);

    for (int i = 0; i < n; ++i)
    {
        s2[i] = s1[n - 1 - i];
    }

    for (int i = 0; i < 1001; ++i)
    {
        for (int j = 0; j < 1001; ++j)
        {
            DP[i][j] = -1;
        }
    }

    int sum = 0;
    sum = Palindrome(n - 1, n - 1);

    if (n - sum <= k)
    {
        puts("Yes");
    }
    else
    {
        puts("No");
    }
}

int Palindrome(int x, int y)
{
    if (x == 0 || y == 0)
    {
        DP[x][y] = 0;
    }

    if (DP[x][y] != -1)
    {
        return DP[x][y];
    }

    if (s1[x] == s2[y])
    {
        DP[x][y] = 1 + Palindrome(x - 1, y - 1);
    }
    else
    {
        DP[x][y] = max(Palindrome(x, y - 1), Palindrome(x - 1, y));
    }

    return DP[x][y];
}

int max(int a, int b)
{
    return a > b ? a : b;
}