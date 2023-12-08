#include <stdio.h>

int check_same(int y);
int check_leap(int y);

int main(void)
{
    int t;
    int year;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i)
    {
        scanf("%d", &year);
        printf("%d\n", check_same(year));
    }

    return 0;
}

int check_leap(int y)
{
    int isLeap = 0;
    if (y % 4 == 0)
    {
        if (y % 100 != 0)
            isLeap = 1;
        else if (y % 400 == 0)
            isLeap = 1;
    }

    return isLeap;
}

int check_same(int y)
{
    int cnt = 0;
    for (int i = y + 1;; ++i)
    {
        if (check_leap(i - 1) == 1 && check_leap(i) == 0)
            cnt += 2;
        else
            cnt++;

        if (cnt % 7 == 0)
            if (check_leap(i) == check_leap(y))
            {
                return i;
                break;
            }
    }
}