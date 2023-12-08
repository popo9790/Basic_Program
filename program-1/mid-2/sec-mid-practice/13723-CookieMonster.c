#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, k;
char number[1000][305];
int How7[1000];
int len[1000];
int ans[1000];

void toNumber(int i, char *s);
int compare1(int a, int b); // compare with 7.
int compare2(int a, int b); // compare without 7.

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    memset(How7, 0, sizeof(How7));

    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i)
    {
        char s[251];

        scanf("%s", s);
        toNumber(i, s);

        ans[i] = i;
    }

    // sort the array by the number of 7 it has.
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n - 1; ++j)
        {
            if (compare1(ans[i], ans[j]))
            {
                int tmp;
                tmp = ans[i];
                ans[i] = ans[j];
                ans[j] = tmp;
            }
        }
    }

    // sort the element we wanna print by th value of cookies.
    for (int i = 0; i < k; ++i)
    {
        for (int j = 0; j < k - 1; ++j)
        {
            if (compare2(ans[i], ans[j]))
            {
                int tmp;
                tmp = ans[i];
                ans[i] = ans[j];
                ans[j] = tmp;
            }
        }
    }

    // Print k-th element of array.
    for (int i = 0; i < k; ++i)
    {
        printf("%s\n", number[ans[i]]);
    }

    return 0;
}

void toNumber(int i, char *s)
{
    char tmp[3];

    for (int index = 0, cur = 0;;)
    {
        if (s[index] == '|' || s[index] == '\0')
        {
            int num;
            char buffer[500] = {'\0'};

            tmp[cur] = '\0';            // In order to use sscanf.
            sscanf(tmp, "%x", &num);    // Turn string to int(hex).
            sprintf(buffer, "%d", num); // Turn int(hex) to string with type int(dec).
            strcat(number[i], buffer);  // Glue to number array.

            if (s[index] == '\0')
            {
                break;
            }

            cur = 0;
            index++;

            continue;
        }

        tmp[cur++] = s[index++]; // copy the element to tmp array.
    }

    // Count the number of 7 element has.
    len[i] = strlen(number[i]);
    for (int index = 0; index < len[i]; ++index)
    {
        if (number[i][index] == '7')
        {
            How7[i]++;
        }
    }
}

int compare1(int a, int b)
{
    int flag = 0;
    if (How7[a] > How7[b])
    {
        flag = 1;
    }
    else if (How7[a] == How7[b])
    {
        if (len[a] > len[b])
        {
            flag = 1;
        }
        else if (len[a] == len[b])
        {
            int r = strcmp(number[a], number[b]);
            if (r > 0)
            {
                flag = 1;
            }
        }
    }

    return flag;
}

int compare2(int a, int b)
{
    int flag = 0;
    if (len[a] < len[b])
    {
        flag = 1;
    }
    else if (len[a] == len[b])
    {
        int r = strcmp(number[a], number[b]);
        if (r < 0)
        {
            flag = 1;
        }
    }

    return flag;
}