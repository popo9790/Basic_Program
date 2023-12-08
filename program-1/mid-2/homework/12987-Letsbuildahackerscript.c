#include <stdio.h>
#include <string.h>

int flag = 1;
char password[21];
char protect[21];
char ans[45];

void hacker(int i, int j, int l, int now);
void display();

int main(void)
{

    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    scanf("%s", password);
    scanf("%s", protect);
    memset(ans, '\0', sizeof(ans));

    hacker(0, 0, strlen(password), 0);

    if (flag)
    {
        printf("What the hack!?\n");
    }

    return 0;
}

void hacker(int i, int j, int l, int now)
{
    if (password[i] == '\0' && protect[j] == '\0')
    {
        ans[now - 1] = '\0';
        display();
        flag = 0;
        return;
    }
    else if (password[i] == '\0' || protect[j] == '\0')
    {
        return;
    }

    if (password[i] == protect[j])
    {
        hacker(i + 1, j + 1, l - 1, now);
    }
    else if (protect[j] == '#')
    {
        for (int a = now, b = 0; b < l; ++a, ++b)
        {
            ans[a] = password[i + b];
            ans[a + 1] = ' ';
            hacker(i + b + 1, j + 1, l - b - 1, a + 2);
        }
    }
    else
    {
        return;
    }
}

void display()
{
    puts(ans);
}