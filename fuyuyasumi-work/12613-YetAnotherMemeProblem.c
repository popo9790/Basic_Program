#include <stdio.h>
#include <string.h>

typedef long long int lli;

lli solve(lli b);
lli check(lli n);

int main(void)
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        lli a, b;
        scanf("%lld %lld", &a, &b);
        printf("%lld\n", check(b) * a);
    }
}

lli check(lli b)
{
    for (lli i = 10, j = 0;; i *= 10, ++j)
        if (b % i == b)
        {
            return j;
            break;
        }
}