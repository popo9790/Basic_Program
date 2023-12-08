#include <bits/stdc++.h>

using namespace std;

const int goalX[] = {-1, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
const int goalY[] = {-1, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
const int dir[4][2] = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};

struct State
{
    int puzzle[4][4];
    int HeuristicVal;
    int CurStep;
    int PrevM;
    int zero_x;
    int zero_y;

    State(const State &rhs)
    {
        this->HeuristicVal = rhs.HeuristicVal;
        this->CurStep = rhs.CurStep;
        this->PrevM = rhs.PrevM;
        this->zero_x = rhs.zero_x;
        this->zero_y = rhs.zero_y;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                this->puzzle[i][j] = rhs.puzzle[i][j];
    }
    State(int input[4][4])
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                this->puzzle[i][j] = input[i][j];
        this->CurStep = 0;
        this->PrevM = -1;
        this->getHeuristic();
    }

    void getHeuristic();
    void getNextState(int, int, int);
    bool operator<(const State rhs) const
    {
        return this->CurStep + this->HeuristicVal > rhs.CurStep + rhs.HeuristicVal;
    }
};

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    int first[4][4];
    int zx, zy;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            cin >> first[i][j];
            if (first[i][j] == 0)
            {
                zx = i;
                zy = j;
            }
        }

    State init(first);
    init.zero_x = zx;
    init.zero_y = zy;

    priority_queue<State> pq;
    pq.push(init);
    while (!pq.empty())
    {
        State cur = pq.top();
        if (cur.HeuristicVal == 0)
            break;
        pq.pop();

        for (int i = 0; i < 4; ++i)
        {
            int Nx = cur.zero_x + dir[i][0];
            int Ny = cur.zero_y + dir[i][1];

            if (0 <= Nx && Nx < 4 && 0 <= Ny && Ny < 4) // 記得要把範圍限制住 不然會爆掉
            {
                if (cur.PrevM + i != 3) // 此處把相反方向的可能排除掉
                {
                    State Next = cur;
                    Next.getNextState(Nx, Ny, i);
                    pq.push(Next);
                }
            }
        }
    }

    if (!pq.empty())
        cout << pq.top().CurStep << endl;
    else
        cout << "-1\n";
}

void State::getHeuristic()
{
    int Htmp = 0;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            int CurNum = this->puzzle[i][j];
            if (CurNum)
            {
                Htmp += abs(i - goalX[CurNum]) + abs(j - goalY[CurNum]);

                if (i == goalX[CurNum])
                    for (int k = j; k < 4; ++k) // 這裡要用 j 是因為我抓住 i 這一個變量 然後對同一列的其他數字作比較
                    {
                        int TestNum = this->puzzle[i][k];
                        // 這裡要記得把 0 的情況剔除 雖然最上面已經排掉 0 了 但這裡是其他數字所以還要再排除一次
                        if (TestNum > 0 && i == goalX[TestNum] && CurNum > TestNum)
                            Htmp += 2;
                    }

                if (j == goalY[CurNum])
                    for (int k = i; k < 4; ++k)
                    {
                        int TestNum = this->puzzle[k][j];
                        if (TestNum > 0 && j == goalY[TestNum] && CurNum > TestNum)
                            Htmp += 2;
                    }
            }
        }
    HeuristicVal = Htmp;
}

void State::getNextState(int Nx, int Ny, int dirNum)
{
    swap(this->puzzle[zero_x][zero_y], this->puzzle[Nx][Ny]);
    this->zero_x = Nx;
    this->zero_y = Ny;
    this->PrevM = dirNum;
    this->CurStep++;
    this->getHeuristic();
}