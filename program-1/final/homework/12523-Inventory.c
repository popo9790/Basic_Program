#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[21];
    int cur_hp;
    int max_hp;
} pokemon;

int ans[100];
int bobosort1(int a, int b);
int bobosort2(int a, int b);

pokemon *inv;
pokemon *arr_init(int n);

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    int n;
    int cont = 0;
    scanf("%d ", &n);
    inv = arr_init(n);

    for (int i = 0; i < n; ++i)
    {
        scanf("%s %d %d", inv[i].name, &inv[i].cur_hp, &inv[i].max_hp);
        if (inv[i].cur_hp == inv[i].max_hp)
        {
            cont++;
        }
        ans[i] = i;
    }

    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - 1 - i; ++j)
        {
            if (bobosort1(ans[j], ans[j + 1]))
            {
                int tmp;
                tmp = ans[j];
                ans[j] = ans[j + 1];
                ans[j + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < n - 1 - cont; ++i)
    {
        for (int j = 0; j < n - 1 - i - cont; ++j)
        {
            if (bobosort2(ans[j], ans[j + 1]))
            {
                int tmp;
                tmp = ans[j];
                ans[j] = ans[j + 1];
                ans[j + 1] = tmp;
            }
        }
    }

    for (int i = 0; i < n; ++i)
    {
        printf("%s %d %d\n", inv[ans[i]].name, inv[ans[i]].cur_hp, inv[ans[i]].max_hp);
    }

    return 0;
}

pokemon *arr_init(int n)
{
    pokemon *arr;

    arr = (pokemon *)malloc(n * sizeof(pokemon));
    return arr;
}

int bobosort1(int a, int b)
{
    int flag = 0;
    if (inv[a].cur_hp == inv[a].max_hp)
    {
        if (inv[b].cur_hp < inv[b].max_hp)
        {
            flag = 1;
        }
    }

    return flag;
}

int bobosort2(int a, int b)
{
    int flag = 0;

    if (inv[a].cur_hp > inv[b].cur_hp)
    {
        flag = 1;
    }
    else if (inv[a].cur_hp == inv[b].cur_hp)
    {
        if (inv[a].max_hp > inv[b].max_hp)
        {
            flag = 1;
        }
    }
    return flag;
}
