#include <bits/stdc++.h>

using namespace std;

int s[12][12];
int lenth[12];
int ans[12];
int cnt = 0;
int n, m;

void solve(int state);
int check();

int main(void)
{
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        cin >> lenth[i];
        for (int j = 0; j < lenth[i]; ++j)
            cin >> s[i][j];
    }
    solve(1);
    cout << cnt << endl;
    return 0;
}

void solve(int state)
{
    if (state == m + 1)
    {
        if (check())
            cnt++;
        return;
    }

    for (int i = 0; i < lenth[state]; ++i)
        ans[s[state][i]]++;
    solve(state + 1);

    for (int i = 0; i < lenth[state]; ++i)
        ans[s[state][i]]--;
    solve(state + 1);
}

int check()
{
    for (int i = 1; i <= n; ++i)
        if (ans[i] == 0)
            return 0;
    return 1;
}