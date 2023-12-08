#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 500

char content[MAX_SIZE];
char input[MAX_SIZE];
char commandtmp[MAX_SIZE];
const char command[][50] = {"/backspace\0", "/newline\0", "/left\0", "/right\0"};
//                           10             8           5        6
int main()
{
    freopen("test.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    memset(content, '\0', sizeof(content));
    memset(input, '\0', sizeof(input));
    memset(commandtmp, '\0', sizeof(commandtmp));

    fgets(input, MAX_SIZE, stdin);

    int l = strlen(input);
    int flag = 0;
    int k = 0;
    int j = 0;
    for (int i = 0; i < l; ++i)
    {
        if (input[i] == '/' || flag)
        {
            flag = 1;

            commandtmp[k++] = input[i];
            commandtmp[k] = '\0';

            if (k == 10 && strcmp(command[0], commandtmp) == 0) // backspace
            {
                if (j > 0)
                {
                    char tmp[MAX_SIZE];
                    strncpy(tmp, content, j - 1);
                    tmp[j - 1] = '\0';

                    strcat(tmp, content + j);
                    strcpy(content, tmp);
                    j--;
                }
                flag = 0;
                k = 0;
            }
            if (k == 8 && strcmp(command[1], commandtmp) == 0) // newline
            {
                content[j++] = '\n';
                flag = 0;
                k = 0;
            }
            if (k == 5 && strcmp(command[2], commandtmp) == 0) // left
            {
                if (j > 0)
                {
                    j--;
                }
                flag = 0;
                k = 0;
            }
            if (k == 6 && strcmp(command[3], commandtmp) == 0) // right
            {
                if (j < strlen(content))
                {
                    j++;
                }
                flag = 0;
                k = 0;
            }
        }
        else
        {
            char tmp[MAX_SIZE];
            strncpy(tmp, content, j);
            tmp[j] = input[i];
            tmp[j + 1] = '\0';

            strcat(tmp, content + j);
            strcpy(content, tmp);

            j++;
        }
    }

    printf("%s", content);

    return 0;
}