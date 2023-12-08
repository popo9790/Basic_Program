#include <bits/stdc++.h>

using namespace std;

struct Myclass
{
    vector<int> seq;
    int Key;
    bool operator<(const Myclass &rhs) const
    {
        return this->Key < rhs.Key;
    }
};

void outputFunc();
void insertVal();
void rangeOut();
void find_reverse(int);
int calVal(const vector<int> &);

set<Myclass> set_arr;
set<int> keyVal;

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    string cmd;
    while (cin >> cmd)
    {
        if (cmd == "output")
            outputFunc();
        else if (cmd == "insert")
            insertVal();
        else if (cmd == "range_out")
            rangeOut();
    }
}

void insertVal()
{
    int val;
    Myclass tmp;
    while (cin >> val)
    {
        if (val == 0)
            break;
        tmp.seq.push_back(val);
    }

    int key = calVal(tmp.seq);
    tmp.Key = key;
    if (keyVal.find(key) == keyVal.end())
    {
        keyVal.insert(key);
        set_arr.insert(tmp);
    }
    else
        find_reverse(key);
}

void rangeOut()
{
    int val;
    int range_1, range_2;
    vector<int> tmp;
    while (cin >> val)
    {
        if (val == 0)
            break;
        tmp.push_back(val);
    }
    range_1 = calVal(tmp);

    tmp.clear();
    while (cin >> val)
    {
        if (val == 0)
            break;
        tmp.push_back(val);
    }
    range_2 = calVal(tmp);

    int cnt = 2;
    for (auto set_it : set_arr)
    {
        if (!cnt)
            break;
        if (range_1 <= set_it.Key && set_it.Key <= range_2)
        {
            for (auto vec_it : set_it.seq)
                cout << vec_it << " ";
            cout << endl;
            cnt--;
        }
    }
}

void outputFunc()
{
    for (auto set_it : set_arr)
    {
        for (auto vec_it : set_it.seq)
            cout << vec_it << " ";
        cout << endl;
    }
}

void find_reverse(int key)
{
    Myclass tmp;
    tmp.Key = key;
    for (auto it = set_arr.begin(); it != set_arr.end(); ++it)
    {
        if ((*it).Key == tmp.Key)
        {
            for (auto vec_it = (*it).seq.rbegin(); vec_it != (*it).seq.rend(); ++vec_it)
                tmp.seq.push_back(*vec_it);
            set_arr.erase(it);
            set_arr.insert(tmp);
            break;
        }
    }
}

int calVal(const vector<int> &tmp)
{
    int len = tmp.size();
    int cnt = 0;
    for (auto it : tmp)
        cnt += it * len--;
    return cnt;
}