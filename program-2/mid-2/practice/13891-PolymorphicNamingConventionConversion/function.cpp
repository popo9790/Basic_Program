#include "function.h"
#include <bits/stdc++.h>

using namespace std;

void CamelCase::convert()
{
    converted = true;
    string tmp;
    stringstream ss;
    ss << this->name;
    this->name.clear();
    while (!ss.eof())
    {
        getline(ss, tmp, '-');
        tmp[0] = toupper(tmp[0]);
        this->name += tmp;
    }
}

void CamelCase::revert()
{
    converted = false;

    string tmp;
    int len = this->name.length();

    for (int i = 0; i < len; ++i)
    {
        if (i > 0 && isupper(this->name[i]))
            tmp += '-';
        tmp += tolower(this->name[i]);
    }
    this->name = tmp;
}