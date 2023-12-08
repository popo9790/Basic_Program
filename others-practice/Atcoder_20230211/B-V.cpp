#include <bits/stdc++.h>

using namespace std;

vector<int> mark;
int ans[205];
int v[205];
int n, m;
void f_print(int cnt);

int main(void)
{
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
    {
        int input;
        cin >> input;
        v[input] = 1;
    }

    for (int i = 1; i <= n; ++i)
    {
        mark.push_back(i);
        if (v[i] == 1)
            mark.push_back(-1);
    }

    int cnt = 0;
    for (int i = 0; i < n + m; ++i)
    {
        if (mark[i] != -1)
        {
            ans[cnt++] = mark[i];
            if (mark[i + 1] != -1)
            {
                f_print(cnt);
                cnt = 0;
            }
        }
    }
}

void f_print(int cnt)
{
    for (int i = cnt - 1; i >= 0; --i)
    {
        cout << ans[i] << ' ';
    }
    memset(ans, -1, sizeof(int));
}