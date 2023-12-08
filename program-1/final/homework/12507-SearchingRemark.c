#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    int i = 0;
    int sum = 0;
    char c;
    char buffer[100];
    char key_word[21];

    scanf("%s", key_word);
    for (int i = 0, l = strlen(key_word); i < l; ++i)
    {
        if (isalpha(key_word[i]))
        {
            key_word[i] = tolower(key_word[i]);
        }
    }

    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '-' || c == '/' || c == ':' || c == '(' ||
            c == ')' || c == '[' || c == ']' || c == '.' || c == ',')
        {
            buffer[i] = '\0';

            if (strcmp(buffer, key_word) == 0)
            {
                sum++;
            }

            i = 0;
            continue;
        }

        if (isalpha(c))
        {
            c = tolower(c);
        }
        buffer[i++] = c;
    }

    printf("%d\n", sum);

    return 0;
}