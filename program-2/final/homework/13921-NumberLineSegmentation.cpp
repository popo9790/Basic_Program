#include <bits/stdc++.h>

using namespace std;

void type_1(int &);
void type_2(int &);

set<int, greater<int>> line;

int main(void)
{
    int N;
    cin >> N;
    while (N--)
    {
        int typ, num;
        cin >> typ >> num;
        if (typ == 1)
            type_1(num);
        else if (typ == 2)
            type_2(num);
    }
}

void type_1(int &num)
{
    auto it = line.find(num);
    if (it == line.end())
        line.insert(num);
    else
        line.erase(it);
}

void type_2(int &num)
{
    auto it = line.lower_bound(num);
    if (it == line.end() || it == line.begin())
        cout << -1 << endl;
    else
        cout << abs((*it--) - (*it)) << endl;
}