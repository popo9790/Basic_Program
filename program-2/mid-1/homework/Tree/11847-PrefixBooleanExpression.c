#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int l, pos;
int state_arr[4]; // 用來儲存ＡＢＣＤ的布林值
char expr[35];

void init(int state);
int PreFix();

int main(void)
{
    scanf("%s", expr);
    l = strlen(expr);
    for (int state = 0; state < 16; state++)
    {
        init(state);
        pos = 0;
        int ans = PreFix();
        printf("%d %d %d %d %d\n", state_arr[0], state_arr[1], state_arr[2], state_arr[3], ans > 0);
        // ans > 0 cuz ans may bigger than 1
    }
}

void init(int state)
{
    for (int i = 0, j = 3, k = 8; i < 4; i++, j--, k /= 2)
        state_arr[i] = (state & (1 << j)) / k;
    // use bitwise mask to create true table
    // Is't important to / k
}

int PreFix()
{
    char c;
    if (pos < l)
    {
        c = expr[pos++];
        if (c >= 'A' && c <= 'D')
            return state_arr[c - 'A'];
        else if (c == '|')
        {
            int a = PreFix();
            int b = PreFix();
            return a + b;
        }
        else if (c == '&')
        {
            int a = PreFix();
            int b = PreFix();
            return a * b;
        }
    }
    return 0;
}