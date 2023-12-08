#include <bits/stdc++.h>

using namespace std;

int main()
{
    int pX[3], pY[3];
    bool cX[6], cY[6];
    memset(cX, true, sizeof(cX));
    memset(cY, true, sizeof(cY));
    for (int i = 0; i < 3; i++)
    {
        cin >> pX[i] >> pY[i];
        cX[pX[i]] = false;
        cY[pY[i]] = false;
    }

    for (int i = 0; i < 6; ++i)
        if (cX[i])
            for (int j = 0; j < 6; ++j)
                if (cY[i])
                    for (int t = 0; t < 3; ++t)
                        if (abs(i - pX[t]) != abs(j - pY[t]))
                        {
                            cout << i << ',' << j << '\n';
                            break;
                        }
}