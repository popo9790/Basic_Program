#include "function.h"
#include <bits/stdc++.h>

using namespace oj;

void oj::insert(std::map<int, String> &ma, int key, const std::string &str)
{
    auto it = ma.find(key);
    std::string tmp;
    if (it == ma.end())
        tmp = str;
    else
    {
        tmp = str + it->second.str;
        ma.erase(it);
    }
    ma.insert(std::pair<int, String>(key, String(tmp)));
}

void oj::output(const std::map<int, String> &ma, int begin, int end)
{
    for (auto it : ma)
        if (begin <= it.first && it.first <= end)
            std::cout << it.second << " ";
}

void oj::erase(std::map<int, String> &ma, int begin, int end)
{
    std::vector<int> deleKey;
    for (auto it : ma)
        if (begin <= it.first && it.first <= end)
            deleKey.push_back(it.first);

    for (auto it : deleKey)
        ma.erase(it);
}

std::ostream &oj::operator<<(std::ostream &output, const std::map<int, String> &ma)
{
    for (auto it : ma)
        output << it.second << " ";
    return output;
}