#include <stdio.h>
#include <string.h>

#define P_NUM 13

typedef struct place place;
typedef struct road road;

struct road
{
    int length;   // The length of the road
    place *place; // Point to the end of the road
};
struct place
{
    int id;         // Index of place, 0 represents the cargo center, and 1~n represents the stores
    int demand;     // Each store has specific units of goods that are demanded to deliver.
    int numOfRoads; // The number of roads that connect with this place
    road roads[P_NUM];
};

place p[P_NUM];
long long gph[P_NUM][P_NUM];
long long dp[13][31][5000];

void distance(place *p, int n);
long long minRoute(place *p, int n);
long long solve(place *p, int n, int place, int goods, int visited);
long long min(long long a, long long b);
void init();

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    p[0].id = p[0].numOfRoads = 0;
    for (int i = 1; i <= n; i++)
    {
        p[i].id = i;
        p[i].numOfRoads = 0;
        scanf("%d", &p[i].demand);
    }
    while (m--)
    {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        (p + a)->roads[p[a].numOfRoads].length = w;
        (p + a)->roads[p[a].numOfRoads++].place = &p[b];
        (p + b)->roads[p[b].numOfRoads].length = w;
        (p + b)->roads[p[b].numOfRoads++].place = &p[a];
    }
    printf("%lld\n", minRoute(p, n + 1));
}

void distance(place *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            gph[i][j] = 1e15;
        }
    }
    for (int i = 0; i < n; i++)
    {
        gph[i][i] = 0;
        for (int j = 0; j < (p + i)->numOfRoads; j++)
        {
            gph[i][(p + i)->roads[j].place->id] = (p + i)->roads[j].length;
        }
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                gph[i][j] = min(gph[i][j], gph[i][k] + gph[k][j]);
            }
        }
    }
}

long long minRoute(place *p, int n)
{
    memset(dp, -1, sizeof(dp));
    distance(p, n);
    return solve(p, n, 0, 30, 1);
}

long long solve(place *p, int n, int place, int goods, int visited)
{
    if (dp[place][goods][visited] != -1)
    {
        return dp[place][goods][visited];
    }
    if (visited == (1 << n) - 1)
    {
        return dp[place][goods][visited] = gph[place][0];
    }

    long long ans = 1e15;
    for (int i = 1; i < n; ++i)
    {
        if (visited & (1 << i))
        {
            continue;
        }
        if (p[i].demand <= goods)
        {
            ans = min(ans, gph[place][i] + solve(p, n, i, goods - p[i].demand, visited | (1 << i)));
        }
        ans = min(ans, gph[place][0] + gph[0][i] + solve(p, n, i, 30 - p[i].demand, visited | (1 << i)));
    }

    return dp[place][goods][visited] = ans;
}

long long min(long long a, long long b)
{
    return a < b ? a : b;
}