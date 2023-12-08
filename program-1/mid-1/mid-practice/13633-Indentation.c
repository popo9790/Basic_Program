#include <stdio.h>

int main()
{
    char c, prev;
    int mode = 0;

    while ((c = getchar()) != EOF)
    {
        if (mode == 0)
        {
            if (c == '\n')
                mode = 1;
        }
        else if (mode == 1)
        {
            if (c == '#')
                mode = 0;
            else if (c == ';')
                c = ' ';
            else if (c == '}')
                mode = 2;
            else
                mode = 3;
        }
        else if (mode == 2)
        {
            if (c == '\n')
                mode = 1;
        }
        else if (mode == 3)
        {
            if (c == '\n')
            {
                if (prev != '{')
                {
                    putchar(';');
                }
                mode = 1;
            }
        }
        putchar(c);
        prev = c;
    }

    return 0;
}