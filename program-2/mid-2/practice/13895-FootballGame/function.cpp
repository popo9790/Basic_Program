#include "function.h"
#include <bits/stdc++.h>

using namespace std;

// [TODO] Implement this function
// Test if any player is at this position.
bool Field::SomeoneIsHere(int x, int y)
{
    for (int it = 0; it < this->p; ++it)
        if (player[it]->IsHere(x, y))
            return true;
    return false;
}

// [TODO] Implement this function
// Find the player who is holding the ball now.
int Field::GetWho()
{
    for (int it = 0; it < this->p; ++it)
        if (player[it]->IsHoldingBall())
            return it;
    return -1;
}

// [TODO] Implement this function
void Field::handleBallKicked(int dx, int dy)
{
    int init_x = ball->GetX();
    int init_y = ball->GetY();

    for (;;)
    {
        init_x += dx;
        init_y += dy;
        if (init_x < 0 || init_x >= n || init_y < 0 || init_y >= m)
        {
            init_x -= dx;
            init_y -= dy;
            break;
        }
        if (SomeoneIsHere(init_x, init_y))
            break;
    }
    ball->SetX(init_x);
    ball->SetY(init_y);
}