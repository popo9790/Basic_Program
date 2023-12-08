#include <stdio.h>

typedef long long ll;

ll k, num;
int flag = 0;
int used[20];
long cost[20];

void eat(int n, ll sum);

int main()
{
    ll sum = 0;

    scanf("%lld %lld", &num, &k);
    for (int i = 0; i < num; ++i)
    {
        scanf("%ld", &cost[i]);
        sum += cost[i];
    }

    if (sum >= k && cost[0] <= k)
    {
        eat(0, 0);
    }

    if (flag)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
}

void eat(int n, ll sum)
{
    if (flag == 1 || sum > k || n >= num)
    {
        return;
    }

    if (sum == k)
    {
        flag = 1;
        return;
    }

    sum += cost[n];
    eat(n + 1, sum);

    sum -= cost[n];
    eat(n + 1, sum);
}