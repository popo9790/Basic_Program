#include <bits/stdc++.h>

using namespace std;

const int N = 200005;

struct Guest
{
    int id;
    int ArrivalTime;
    int size;
    int Duration;
};

auto Arrival_cmp = [](const Guest lhs, const Guest rhs)
{
    return lhs.ArrivalTime < rhs.ArrivalTime;
};
auto Group_cmp = [](const Guest lhs, const Guest rhs)
{
    return lhs.size == rhs.size ? lhs.ArrivalTime > rhs.ArrivalTime : lhs.size < rhs.size;
};

Guest arr[N];
int TimeAns[N];
set<Guest, decltype(Arrival_cmp)> Arrival_arr(Arrival_cmp);
set<Guest, decltype(Group_cmp)> Group_arr(Group_cmp);
map<int, int> table_avl;             // <typ, num>
multiset<pair<int, int>> table_used; // <duration, typ>

void ReleaseTable(int);
bool getTable(int);

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i].ArrivalTime >> arr[i].size >> arr[i].Duration;
        arr[i].id = i;
    }
    for (int i = 0; i < m; ++i)
    {
        int typ, num;
        cin >> typ >> num;
        table_avl[typ] = num;
    }
    for (int i = 0; i < n; ++i)
    {
        ReleaseTable(arr[i].ArrivalTime - 1);

        Arrival_arr.insert(arr[i]);
        Group_arr.insert(arr[i]);

        ReleaseTable(arr[i].ArrivalTime);
        getTable(arr[i].ArrivalTime);
    }

    ReleaseTable(1e9);

    for (int i = 0; i < n; ++i)
        cout << TimeAns[i] << endl;
}

void ReleaseTable(int time)
{
    while (table_used.size() && table_used.begin()->first <= time)
    {
        int ReleaseTime = table_used.begin()->first;
        int Typ = table_used.begin()->second;

        table_avl[Typ]++;
        table_used.erase(table_used.begin());
        if (table_used.size() && table_used.begin()->first == ReleaseTime)
            continue;

        while (getTable(ReleaseTime))
            ;
    }
}

bool getTable(int time)
{
    if (table_avl.empty() || Arrival_arr.empty()) // 空桌 或 0 客人時要跳過
        return false;

    Guest Kyaku = *Arrival_arr.begin();
    auto findTable = table_avl.lower_bound(Kyaku.size);

    if (findTable == table_avl.end())
    {
        int LargeSize = table_avl.rbegin()->first;
        auto it = Group_arr.upper_bound(Guest{0, 0, LargeSize, 0}); // upper_bound 回傳 > Key 的第一個值
        if (it == Group_arr.begin())
            return false;

        Kyaku = *(--it);
        findTable = table_avl.lower_bound(Kyaku.size);
    }

    int TableTyp = findTable->first;
    table_avl[TableTyp]--;
    if (table_avl[TableTyp] == 0)
        table_avl.erase(TableTyp);
    table_used.insert({time + Kyaku.Duration, TableTyp});

    TimeAns[Kyaku.id] = time;
    Arrival_arr.erase(Kyaku);
    Group_arr.erase(Kyaku);

    return true;
}