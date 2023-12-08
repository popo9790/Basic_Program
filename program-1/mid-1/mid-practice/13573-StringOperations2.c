#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{

    char s[1000001], subs[1000001], alph[26];
    int n;

    scanf(" %s", s);
    scanf(" %d", &n);

    for (int i = 0; i < 26; ++i)
    {
        alph[i] = 'a' + i;
    }

    int oper[n];
    int first[n], second[n];

    memset(first, 0, n);
    memset(second, 0, n);
    memset(subs, 0, 1000001);

    for (int i = 0; i < n; ++i)
    {
        scanf(" %d", &oper[i]);
        if (oper[i] == 1)
        {
            char a, b;
            scanf(" %c %c", &a, &b);
            first[i] = a;
            second[i] = b;
        }
        else
        {
            int a;
            char b;
            scanf(" %d %c", &a, &b);
            first[i] = a;
            second[i] = b;
        }
    }

    for (int i = n - 1; i >= 0; --i)
    {
        if (oper[i] == 1)
        {
            alph[first[i] - 'a'] = alph[second[i] - 'a'];
        }
        else
        {
            if (subs[first[i]] == 0)
            {
                subs[first[i]] = alph[second[i] - 'a'];
            }
        }
    }

    for (int i = 0, l = strlen(s); i < l; ++i)
    {
        if (subs[i] != 0)
        {
            printf("%c", subs[i]);
        }
        else
        {
            printf("%c", alph[s[i] - 'a']);
        }
    }
    printf("\n");

    return 0;
}