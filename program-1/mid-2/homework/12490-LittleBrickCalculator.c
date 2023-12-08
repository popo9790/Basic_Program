#include <stdio.h>

#define maxn 1000

char input[1000010];

int solver(int **ptr, int *sum, char *s);

int main()
{
    int sum = 0;
    int a[maxn];
    int *ptr[maxn];

    for (int i = 0; i < maxn; i++)
    {
        a[i] = 0;
        ptr[i] = &a[i];
    }

    scanf("%s", input);

    int n = solver(ptr, &sum, input);

    printf("%d", a[0]);
    for (int i = 1; i < n; i++)
    {
        printf(" %d", a[i]);
    }

    printf("\n%d\n", sum);

    return 0;
}

int solver(int **ptr, int *sum, char *s)
{
    int n = 0, l = 0, z = 0;
    char num[100001];

    for (int i = 0, j = 0;; ++i)
    {
        if (s[i] == '\0')
        {
            if (l != 0)
            {
                for (int a = l - 1, b = 1; a >= 0; --a, b *= 10)
                {
                    if (num[a] == '-')
                    {
                        (*ptr)[j] *= -1;
                    }
                    else
                    {
                        (*ptr)[j] += (num[a] - '0') * b;
                    }
                }
                *sum += (*ptr)[j];
                j++;
                n++;
            }
            break;
        }

        if (s[i] == '-')
        {
            if (l != 0)
            {
                for (int a = l - 1, b = 1; a >= 0; --a, b *= 10)
                {
                    if (num[a] == '-')
                    {
                        (*ptr)[j] *= -1;
                    }
                    else
                    {
                        (*ptr)[j] += (num[a] - '0') * b;
                    }
                }
                *sum += (*ptr)[j];
                j++;
                n++;
            }
            z = 0;
            l = 0;

            num[z++] = s[i];
            l++;
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
            num[z++] = s[i];
            l++;
        }
        else
        {
            if (l != 0)
            {
                for (int a = l - 1, b = 1; a >= 0; --a, b *= 10)
                {
                    if (num[a] == '-')
                    {
                        (*ptr)[j] *= -1;
                    }
                    else
                    {
                        (*ptr)[j] += (num[a] - '0') * b;
                    }
                }
                *sum += (*ptr)[j];
                j++;
                n++;
            }
            l = 0;
            z = 0;
        }
    }

    return n;
}