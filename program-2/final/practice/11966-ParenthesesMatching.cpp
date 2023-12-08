#include <bits/stdc++.h>

using namespace std;

map<char, char> syntax = {{'<', '>'}, {'(', ')'}, {'[', ']'}, {'{', '}'}};

int main(void)
{
    freopen("test.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    int n;
    string str;
    cin >> n;
    getline(cin, str); // 這可以吃整行包含換行空白
    for (int i = 1; i <= n; ++i)
    {
        bool flag = true;
        stack<char> tube;
        getline(cin, str);

        for (auto c : str)
        {
            if (c == '<' || c == '[' || c == '{' || c == '(')
                tube.push(c);

            if (c == '>' || c == ']' || c == '}' || c == ')')
            {
                if (tube.empty() || c != syntax[tube.top()])
                {
                    flag = false;
                    break;
                }
                if (c == syntax[tube.top()])
                    tube.pop();
            }
        }
        if (tube.empty() && flag)
            cout << "Case " << i << ": Yes\n";
        else
            cout << "Case " << i << ": No\n";
    }
}