#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX 1000000

int sum;
char key_word[21];
char line[MAX];
char delim[] = " \n-/:()[],.";

int main(void)
{
    scanf("%s", key_word);
    for (int i = 0, l = strlen(key_word); i < l; ++i)
        key_word[i] = tolower(key_word[i]);
    while (fgets(line, MAX, stdin) != NULL)
    {
        char *tmp;
        tmp = strtok(line, delim);
        while (tmp != NULL)
        {
            for (int i = 0, l = strlen(tmp); i < l; ++i)
                tmp[i] = tolower(tmp[i]);
            if (strcmp(key_word, tmp) == 0)
                sum++;
            tmp = strtok(NULL, delim);
        }
    }
    printf("%d\n", sum);
}