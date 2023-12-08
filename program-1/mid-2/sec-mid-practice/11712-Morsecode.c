#include <stdio.h>
#include <string.h>

char code[26][26] = {
    {"*_\0"},   // A
    {"_***\0"}, // B
    {"_*_*\0"}, // C
    {"_**\0"},  // D
    {"*\0"},    // E
    {"**_*\0"}, // F
    {"__*\0"},  // G
    {"****\0"}, // H
    {"**\0"},   // I
    {"*___\0"}, // J
    {"_*_\0"},  // K
    {"*_**\0"}, // L
    {"__\0"},   // M
    {"_*\0"},   // N
    {"___\0"},  // O
    {"*__*\0"}, // P
    {"__*_\0"}, // Q
    {"*_*\0"},  // R
    {"***\0"},  // S
    {"_\0"},    // T
    {"**_\0"},  // U
    {"***_\0"}, // V
    {"*__\0"},  // W
    {"_**_\0"}, // X
    {"_*__\0"}, // Y
    {"__**\0"}, // Z
};

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    int n;
    char s[1000];
    char cos[1000];
    char ans[20];

    memset(cos, '\0', sizeof(cos));

    scanf("%d", &n);
    scanf("%s", s);

    for (int i = 0, j = 0, count = 0, dot = 0; i <= n; ++i)
    {
        if (s[i] == '.' || s[i] == '\0')
        {
            if (s[i] == '.')
                dot++;

            if (count == 3)
            {
                cos[j++] = '_';
            }
            else if (count == 1)
            {
                cos[j++] = '*';
            }

            if (dot == 3 && s[i + 1] == '=')
            {
                cos[j++] = '|';
                dot = 0;
            }
            else if (dot == 7)
            {
                cos[j++] = 'B';
                dot = 0;
            }

            count = 0;
        }

        if (s[i] == '=')
        {
            dot = 0;
            count++;
        }
    }

    for (int i = 0, j = 0, l = strlen(cos); i <= l; ++i)
    {
        if (cos[i] == '|' || cos[i] == '\0' || cos[i] == 'B')
        {
            ans[j] = '\0'; // cuz we wanna use strcmp to compare string
            for (int a = 0; a < 26; ++a)
            {
                if (strcmp(ans, code[a]) == 0)
                {
                    putchar('A' + a);
                    memset(ans, '\0', sizeof(ans));
                    j = 0;
                    break;
                }
            }

            if (cos[i] == 'B')
                putchar(' ');

            continue;
        }
        ans[j++] = cos[i];
    }
    puts("");

    return 0;
}