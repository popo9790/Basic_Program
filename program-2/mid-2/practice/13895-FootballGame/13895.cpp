#include "function.h"
#include <iostream>

using namespace std;

int main()
{
    freopen("test.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    int n, m, p;
    cin >> n >> m >> p;
    // Game Preparation
    Field *f = new Field(n, m, p);
    // Game Start
    cout << "Game Start\n";
    int rounds;
    cin >> rounds;
    f->GameStart(rounds);
    return 0;
}
