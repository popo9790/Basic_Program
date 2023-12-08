#include <stdio.h>

int main(void)
{
    long long n, m;
    scanf(" %lld", &n);

    long long num[n], presum[n + 1];
    presum[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        scanf(" %lld", &num[i - 1]);
        presum[i] = presum[i - 1] + num[i - 1];
    }

    scanf(" %lld", &m);
    for (int i = 0; i < m; ++i)
    {
        long long l, r;
        scanf(" %lld %lld", &l, &r);

        if (l == r)
        {
            printf("%lld\n", num[l - 1]);
        }
        else
        {
            printf("%lld\n", presum[r] - presum[l - 1]);
        }
    }
    return 0;
}