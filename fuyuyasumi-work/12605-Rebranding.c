#include <stdio.h>

char name[200001];
char alph[26];
int n, m;

void init();
int alph_find(char c);

int main(void)
{
    init();
    scanf("%d %d", &n, &m);
    scanf("%s", name);
    for (int i = 0; i < m; ++i)
    {
        char x, y;
        scanf(" %c %c ", &x, &y);
        int st = alph_find(x);
        int nd = alph_find(y);

        alph[st] = y;
        alph[nd] = x;
    }

    for (int i = 0; i < n; ++i)
        printf("%c", alph[name[i] - 'a']);
    puts("");

    return 0;
}

void init()
{
    for (int i = 0; i < 26; ++i)
        alph[i] = 'a' + i;
}

int alph_find(char c)
{
    for (int i = 0; i < 26; ++i)
        if (alph[i] == c)
        {
            return i;
            break;
        }
}
