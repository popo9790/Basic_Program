#include <stdio.h>

int side(int n);
void run(int r, int c, int n);
void replace(int r, int c, int n);
void store(int r, int c, int n);
void display();

void up(int r, int c, int n);
void left(int r, int c, int n);
void right(int r, int c, int n);
void down(int r, int c, int n);

int num;
int cp[1024 * 8][1024 * 8], cptmp[1024 * 8][1024 * 8];

int main(void)
{
    scanf("%d", &num);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if ((i == 0 && j == 0) || (i == 0 && j == 3) || (i == 3 && j == 0) || (i == 3 && j == 3))
            {
                cptmp[i][j] = 0;
            }
            else
            {
                cptmp[i][j] = 1;
            }
        }
    }

    run(0, 0, num);

    display();
}

int side(int n)
{
    int sum = 1;
    for (int i = 0; i < n - 1; ++i)
    {
        sum *= 2;
    }
    sum *= 4;

    return sum;
}

void run(int r, int c, int n)
{

    if (n == 1)
    {
        return;
    }

    int a = side(n - 1);
    if (n % 2 == 0)
    {
        run(r, c, n - 1);

        replace(r, c, a);
        replace(r, c + a, a);
        replace(r + a, c, a);
        replace(r + a, c + a, a);
    }
    else
    {
        run(r + a / 2, c + a / 2, n - 1);

        up(r, c + a / 2, n - 1);
        down(r + a + a / 2, c + a / 2, n - 1);
        left(r + a / 2, c, n - 1);
        right(r + a / 2, c + a + a / 2, n - 1);

        store(r, c, side(n));
    }
}

void replace(int r, int c, int n)
{
    for (int i = r; i < r + n; ++i)
    {
        for (int j = c; j < c + n; ++j)
        {
            cp[i][j] = cptmp[i - r][j - c];
        }
    }
}

void up(int r, int c, int n)
{
    for (int i = r, a = side(n); i < r + a / 2; ++i)
    {
        for (int j = c; j < c + a; ++j)
        {
            if (j >= c + a / 4 && j < c + a - a / 4 && i < r + a / 4)
            {
                cp[i][j] = 0;
            }
            else
            {
                cp[i][j] = 1;
            }
        }
    }
}

void down(int r, int c, int n)
{
    for (int i = r, a = side(n); i < r + a / 2; ++i)
    {
        for (int j = c; j < c + a; ++j)
        {
            if (j >= c + a / 4 && j < c + a - a / 4 && i >= r + a / 4)
            {
                cp[i][j] = 0;
            }
            else
            {
                cp[i][j] = 1;
            }
        }
    }
}

void left(int r, int c, int n)
{
    for (int i = r, a = side(n); i < r + a; ++i)
    {
        for (int j = c; j < c + a / 2; ++j)
        {
            if (i >= r + a / 4 && i < r + a - a / 4 && j < c + a / 4)
            {
                cp[i][j] = 0;
            }
            else
            {
                cp[i][j] = 1;
            }
        }
    }
}

void right(int r, int c, int n)
{
    for (int i = r, a = side(n); i < r + a; ++i)
    {
        for (int j = c; j < c + a / 2; ++j)
        {
            if (i >= r + a / 4 && i < r + a - a / 4 && j >= c + a / 4)
            {
                cp[i][j] = 0;
            }
            else
            {
                cp[i][j] = 1;
            }
        }
    }
}

void store(int r, int c, int n)
{
    for (int i = r; i < r + n; ++i)
    {
        for (int j = c; j < c + n; ++j)
        {
            cptmp[i - r][j - c] = cp[i][j];
        }
    }
}

void display()
{
    for (int i = 0, a = side(num); i < a; ++i)
    {
        for (int j = 0; j < a; ++j)
        {
            if (cp[i][j] == 1)
            {
                printf("#");
            }
            else if (cp[i][j] == 0)
            {
                printf(".");
            }
        }
        puts("");
    }
}
