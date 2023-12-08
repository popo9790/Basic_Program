#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[1002];

    while (scanf(" %s", s) != EOF)
    {
        int l = strlen(s), count = 1, subl = 0;
        char subs[1001];

        for (int i = 0; i < l; ++i)
        {
            if (s[i] == s[i + 1])
            {
                count++;
            }
            else
            {
                printf("%d", count);
                for (int j = 1000, z = 4; j >= 1; j = j / 10, --z)
                {
                    if (count / j != 0)
                    {
                        subl += z;
                        break;
                    }
                }

                count = 1;
                if (s[i] >= '0' && s[i] <= '9')
                {
                    printf("'%c'", s[i]);
                    subl += 3;
                }
                else
                {
                    printf("%c", s[i]);
                    subl++;
                }
            }
        }

        printf("\n");
        if ((float)subl / l < 1.0)
        {
            printf("compress rate:%6.3f\n", (float)subl / l);
        }
        else
        {
            printf("the string can't zip\n");
        }
    }

    return 0;
}