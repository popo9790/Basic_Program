#include <bits/stdc++.h>

using namespace std;

int n, m;
bool road[2005][2005];

void solve(int stateA, int stateB);

int main(void)
{
    int t;
    cin >> t;
    for (int i = 0; i < t; ++i)
    {
        memset(road, false, sizeof(road));
        cin >> n >> m;
        for (int j = 0; j < m; ++j)
        {
            int a, b;
            cin >> a >> b;
            road[a][b] = true;
            road[b][a] = true;
        }
        solve(1, n);
    }
}

void solve(int stateA, int stateB)
{
}