#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>

#define maxsize 10000
class INT
{
public:
    INT();
    void mulby10();
    INT operator=(INT);
    INT operator+(INT);
    INT operator*(INT);
    friend std::istream &operator>>(std::istream &, INT &);
    friend std::ostream &operator<<(std::ostream &, INT);

private:
    char data[maxsize + 1];
    int len;
};

#endif
