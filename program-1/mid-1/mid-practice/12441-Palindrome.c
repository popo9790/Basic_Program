#include <stdio.h>
#include <string.h>

int main(void)
{
    char word[100001];

    while (scanf(" %s", word) != EOF)
    {
        int l = strlen(word), flag = 1;
        for (int i = 0; i < l; ++i)
        {
            if (word[i] != word[l - 1 - i])
            {
                flag = 0;
                break;
            }
        }
        if (flag)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }

    return 0;
}