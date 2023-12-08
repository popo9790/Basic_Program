#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 10;
bool dp[N];
int prob[11];
int trap[100005];
int des;
bool flag = false;
int p, t;

void solve(int state);

int main(void)
{
    cin >> p;
    for (int i = 0; i < p; ++i)
        cin >> prob[i];

    cin >> t;
    for (int i = 0; i < t; ++i)
    {
        int input;
        cin >> input;
        dp[input] = true;
    }

    cin >> des;
    solve(0);

    if (flag)
        cout << "Yes\n";
    else
        cout << "No\n";
}

void solve(int state)
{
    if (state == des)
        flag = true;
    if (flag || state > des)
        return;

    for (int i = 0; i < p; ++i)
    {
        int new_state;
        new_state = state + prob[i];

        if (!dp[new_state])
        {
            dp[new_state] = true;
            solve(new_state);
        }
    }
}