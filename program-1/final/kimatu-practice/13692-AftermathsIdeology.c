#include <stdio.h>
#include <string.h>

#define MAX_char 1000000

int n, tmp;
char alph[100000][26];
char s[MAX_char + 1];

void init();
void cpyalph(int i);
void swap(int a, int b);

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    scanf("%s", s);
    scanf("%d", &n);

    int op[n], first[n], second[n];
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &op[i]);
        if (op[i] == 1)
        {
            char a, b;
            scanf(" %c %c", &a, &b);
            first[i] = a;
            second[i] = b;
        }
        else if (op[i] == 2)
        {
            int a;
            char b;
            scanf(" %d %c", &a, &b);
            first[i] = a;
            second[i] = b;
        }
        else if (op[i] == 3)
        {
            int a, b;
            scanf(" %d %d", &a, &b);
            first[i] = a;
            second[i] = b;
        }
    }
    init();

    for (int i = n - 1; i >= 0; --i)
    {
        if (op[i] == 1)
        {
            alph[i][first[i] - 'a'] = alph[i][second[i] - 'a'];
        }
        cpyalph(i);
    }
    for (int i = 0, l = strlen(s); i < l; ++i)
    {
        s[i] = alph[0][s[i] - 'a'];
    }

    for (int i = 0; i < n; ++i)
    {
        if (op[i] == 2)
        {
            s[first[i]] = alph[i][second[i] - 'a'];
        }
        else if (op[i] == 3)
        {
            swap(first[i], second[i]);
        }
    }

    puts(s);

    return 0;
}

void init()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 26; ++j)
        {
            alph[i][j] = j + 'a';
        }
    }
}

void cpyalph(int i)
{
    if (i != 0)
    {
        for (int j = 0; j < 26; ++j)
        {
            alph[i - 1][j] = alph[i][j];
        }
    }
}

void swap(int a, int b)
{
    char tmp;
    tmp = s[a];
    s[a] = s[b];
    s[b] = tmp;
}
