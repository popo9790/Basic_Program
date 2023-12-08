#include "function.h"
#include <string.h>

String_Calculator::String_Calculator(const string input)
    : s(input){};

String_Calculator &String_Calculator::Add(const string substr)
{
    s += substr;
    return *this;
}

String_Calculator &String_Calculator::Subtract(const string substr)
{
    int found = s.find(substr);
    if (found != string::npos)
        s.erase(found, substr.length());
    else
        s = "error";
    return *this;
}

String_Calculator &String_Calculator::DividedBy(const string substr)
{
    int found = s.find(substr);
    int cnt = 0;
    while (found != string::npos)
    {
        cnt++;
        found = s.find(substr, found + 1);
    }
    s = to_string(cnt); // to_string is important
    return *this;
}

void String_Calculator::output() const
{
    cout << s << endl;
}