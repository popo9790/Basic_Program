#include "function.h"
#include <bits/stdc++.h>

using namespace std;

INT INT::operator*(INT rhs)
{
    INT tmp = *this;
    INT sum;
    for (int i = 0; i < rhs.len; ++i)
    {
        int time = rhs.data[i];
        while (time--)
            sum = sum + tmp;
        tmp.mulby10();
    }
    return sum;
}