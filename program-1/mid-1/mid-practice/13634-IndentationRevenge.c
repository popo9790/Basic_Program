#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char s[1000001];

int StringIpunt()
{
    char c;
    int i = 0;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        s[i++] = c;
    }
    s[i] = 0;

    if (c == EOF)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void SpaceChange(int l)
{
    for (int i = 0; i < l; ++i)
    {
        if (s[i] == ' ')
        {
            s[i] = ';';
        }
        else
        {
            break;
        }
    }
}

int main(void)
{
    while (StringIpunt())
    {
        int l = strlen(s);

        if (s[0] == '#')
        {
        }
        else
        {
            SpaceChange(l);
            if (s[l - 1] == ';')
            {
                s[l - 1] = '\0';
            }
        }

        printf("%s\n", s);
        memset(s, 0, sizeof(s));
    }

    printf("// surprise<3\n");

    return 0;
}