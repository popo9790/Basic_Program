#include <bits/stdc++.h>

using namespace std;

map<string, string> poki;

void init();
int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    init();
    int n;
    cin >> n;
    while (n--)
    {
        string name, school, tmp;
        cin >> name >> school;

        for (int i = 0; i < 2; ++i)
            tmp.push_back(name[i]);

        if (tmp == "Ta" && name.size() >= 4)
            for (int i = 2; i < 4; ++i)
                tmp.push_back(name[i]);

        auto fd = poki.find(tmp);
        if (fd != poki.end())
            cout << name << " the " << school << " " << fd->second << endl;
        else
            cout << name << " is looking for a Chinese tutor, too!\n";
    }
}

void init()
{
    poki.insert(pair<string, string>("Wa", "Waninoko"));
    poki.insert(pair<string, string>("Mi", "Milotic"));
    poki.insert(pair<string, string>("Ma", "Magikarp"));
    poki.insert(pair<string, string>("Va", "Vaporeon"));
    poki.insert(pair<string, string>("Sh", "Sharpedo"));
    poki.insert(pair<string, string>("Tapu", "Tapu Fini"));
    poki.insert(pair<string, string>("Em", "Empoleon"));
    poki.insert(pair<string, string>("La", "Lapras"));
    poki.insert(pair<string, string>("Pi", "Pikachu"));
    poki.insert(pair<string, string>("Pe", "Pikachu"));
    poki.insert(pair<string, string>("Me", "Mega Gyarados"));
}
