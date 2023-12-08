#include <bits/stdc++.h>

using namespace std;

#define INF 100005

class graph
{
private:
    vector<vector<int>> AdjList;
    vector<int> dis;
    vector<int> min_dis;
    vector<int> diatown;
    vector<bool> visited;

public:
    graph(const int N)
    {
        AdjList.resize(N);
        dis.resize(N);
        min_dis.resize(N);
        visited.resize(N);

        fill(visited.begin(), visited.end(), false);
        fill(min_dis.begin(), min_dis.end(), INF);
        fill(dis.begin(), dis.end(), INF);
    }
    void BFS();
    void InsertRoad(int a, int b)
    {
        AdjList[a].push_back(b);
        AdjList[b].push_back(a);
    }
    void InsertDia(int dia)
    {
        diatown.push_back(dia);
    }
    void Output()
    {
        for (auto it : min_dis)
            cout << it << endl;
    }
};

// my town cnt from 0;
int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    int townNum, road, diaNum;
    cin >> townNum >> road >> diaNum;

    graph mymap(townNum);
    for (int i = 0; i < road; ++i)
    {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        mymap.InsertRoad(a, b);
    }
    for (int i = 0; i < diaNum; ++i)
    {
        int dia;
        cin >> dia;
        dia--;
        mymap.InsertDia(dia);
    }
    mymap.BFS();
    mymap.Output();
}

void graph::BFS()
{
    queue<int> q;
    for (auto it : diatown)
    {
        visited[it] = true;
        dis[it] = 0;
        min_dis[it] = 0;
        q.push(it);
    }

    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (auto it : AdjList[cur])
        {
            if (!visited[it])
            {
                dis[it] = dis[cur] + 1;
                if (dis[it] < min_dis[it])
                {
                    min_dis[it] = dis[it];
                    visited[it] = true;
                    q.push(it);
                }
            }
        }
    }
}