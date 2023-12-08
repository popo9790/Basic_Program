#include <bits/stdc++.h>

using namespace std;

int MaxLv, Hp, MHp, MDmg;
bool vis[20][310][410]; // 重要 必須要有 DP 才能夠避免重複跑到相同的 State
vector<pair<int, int>> LvUp;

struct State
{
    State(int lv = 0, int myh = Hp, int mhp = MHp) : Level(lv), MyHp(myh), MonHp(mhp), dis(0){};
    int Level;
    int MyHp;
    int MonHp;
    int dis;
};

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    cin >> MaxLv >> Hp >> MHp >> MDmg;
    for (int i = 0; i < MaxLv; ++i)
    {
        int Dmg, Heal;
        cin >> Dmg >> Heal;
        LvUp.push_back({Dmg, Heal});
    }

    queue<State> q;
    State init;
    vis[init.Level][init.MyHp][init.MonHp] = true;
    q.push(init);

    while (!q.empty())
    {
        State cur = q.front();
        if (cur.MonHp <= 0)
            break;
        q.pop();

        int NDmg = LvUp[cur.Level].first;
        int NHeal = LvUp[cur.Level].second;

        // Attack
        if (cur.MonHp - NDmg <= 0 || cur.MyHp - MDmg > 0)
        {
            State next(cur.Level, cur.MyHp - MDmg, cur.MonHp - NDmg);
            next.dis = cur.dis + 1;
            if (!vis[next.Level][next.MyHp][next.MonHp])
            {
                vis[next.Level][next.MyHp][next.MonHp] = true;
                q.push(next);
            }
        }

        // Heal
        int AfterHeal = cur.MyHp + NHeal;
        if (AfterHeal >= Hp)
            AfterHeal = Hp;
        if (AfterHeal - MDmg > 0)
        {
            State next(cur.Level, AfterHeal - MDmg, cur.MonHp);
            next.dis = cur.dis + 1;
            if (!vis[next.Level][next.MyHp][next.MonHp])
            {
                vis[next.Level][next.MyHp][next.MonHp] = true;
                q.push(next);
            }
        }

        // Level Up
        if (cur.MyHp - MDmg > 0 && cur.Level + 1 < MaxLv)
        {
            State next(cur.Level + 1, cur.MyHp - MDmg, cur.MonHp);
            next.dis = cur.dis + 1;
            if (!vis[next.Level][next.MyHp][next.MonHp])
            {
                vis[next.Level][next.MyHp][next.MonHp] = true;
                q.push(next);
            }
        }
    }

    if (!q.empty())
        cout << q.front().dis << endl;
    else
        cout << -1 << endl;
}