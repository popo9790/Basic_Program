#include <bits/stdc++.h>

using namespace std;

struct Map
{
    Map(char r = 0, int x = 0, int y = 0) : road(r), x(x), y(y), visited(false){};
    int x;
    int y;
    char road;
    int dis;
    bool visited;
};

int st_x, st_y;
Map mymap[1005][1005];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int n, m;

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
        {
            cin >> mymap[i][j].road;
            if (mymap[i][j].road == 'P')
            {
                st_x = i;
                st_y = j;
            }
            mymap[i][j].dis = 0;
            mymap[i][j].x = i;
            mymap[i][j].y = j;
        }

    queue<Map> q;
    mymap[st_x][st_y].visited = true;
    q.push(mymap[st_x][st_y]);
    while (!q.empty())
    {
        Map cur = q.front();
        if (cur.road == '@')
            break;
        q.pop();

        for (int i = 0; i < 4; ++i)
        {
            int nx = cur.x + dir[i][0];
            int ny = cur.y + dir[i][1];
            if (0 <= nx && nx < n && 0 <= ny && ny < m && mymap[nx][ny].road != '#')
            {
                if (!mymap[nx][ny].visited)
                {
                    mymap[nx][ny].dis = cur.dis + 1;
                    mymap[nx][ny].visited = true;
                    q.push(mymap[nx][ny]);
                }
            }
        }
    }
    if (q.empty())
        cout << -1 << endl;
    else
        cout << q.front().dis << endl;
}