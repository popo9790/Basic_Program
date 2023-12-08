#include <bits/stdc++.h>

using namespace std;

int main(void)
{
    string s;
    cin >> s;
    for (auto i = s.begin(); i != s.end(); ++i)
    {
        if (*i == '1')
            cout << '0';
        else
            cout << '1';
    }
    puts("");
}