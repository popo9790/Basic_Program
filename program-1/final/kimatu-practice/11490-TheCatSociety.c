#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_nun 10000

typedef struct
{
    char name[31];
    int occu;
    int age;
} Cat;

Cat cat[MAX_nun];
int ans[MAX_nun];

void check(char c, int i);
int change(const void *i, const void *j);

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    int a, b;
    while (scanf("%d %d", &a, &b) != EOF)
    {
        for (int i = 0; i < a; ++i)
        {
            char c[20];
            scanf("%s %s %d", cat[i].name, c, &cat[i].age);
            check(c[0], i);
            ans[i] = i;
        }

        qsort(ans, a, sizeof(ans[0]), change);

        if (b > a)
            b = a;
        for (int i = 0; i < b; ++i)
        {
            printf("%s\n", cat[ans[i]].name);
        }
    }
}

void check(char c, int i)
{
    switch (c)
    {
    case 'e':
        cat[i].occu = 1;
        break;
    case 'n':
        cat[i].occu = 2;
        break;
    case 'k':
        cat[i].occu = 3;
        break;
    case 'w':
        cat[i].occu = 4;
        break;
    case 'a':
        cat[i].occu = 5;
        break;
    case 'm':
        cat[i].occu = 6;
        break;
    case 'd':
        cat[i].occu = 7;
        break;
    case 'l':
        cat[i].occu = 8;
        break;
    }
}

int change(const void *i, const void *j)
{
    int a = *(int *)i;
    int b = *(int *)j;

    if (cat[a].occu > cat[b].occu)
    {
        return 1;
    }
    else if (cat[a].occu == cat[b].occu)
    {
        if (cat[a].occu == 5)
        {
            if (cat[a].age > cat[b].age)
            {
                return 1;
            }
            else if (cat[a].age == cat[b].age)
            {
                if (strcmp(cat[a].name, cat[b].name) > 0)
                {
                    return 1;
                }
            }

            return 0;
        }

        if (cat[a].age < cat[b].age)
        {
            return 1;
        }
        else if (cat[a].age == cat[b].age)
        {
            if (strcmp(cat[a].name, cat[b].name) > 0)
            {
                return 1;
            }
        }
    }
    return 0;
}