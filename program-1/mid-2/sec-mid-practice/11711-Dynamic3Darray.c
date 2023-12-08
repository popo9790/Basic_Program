#include <stdio.h>
#include <stdlib.h>

unsigned ***new_3d_array(unsigned n, unsigned m, unsigned k);
void delete_3d_array(unsigned ***arr);

unsigned random_seed = 7122;
unsigned Random()
{
    return random_seed = random_seed * 0xdefaced + 1;
}

int main()
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    int n, m, k, _;

    scanf("%d%d%d%d%u", &_, &n, &m, &k, &random_seed);
    while (_--)
    {
        unsigned ***arr = new_3d_array(n, m, k);
        int i, j, l;

        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < m; ++j)
            {
                for (l = 0; l < k; ++l)
                {
                    arr[i][j][l] = Random();
                }
            }
        }

        for (i = 0; i < 5; ++i)
        {
            unsigned a, b, c;

            a = Random() % n;
            b = Random() % m;
            c = Random() % k;

            if (i)
            {
                putchar(' ');
            }
            printf("%u", arr[a][b][c]);
        }

        puts("");
        delete_3d_array(arr);
    }

    return 0;
}

unsigned ***new_3d_array(unsigned n, unsigned m, unsigned k)
{
    unsigned ***arr1;
    unsigned **arr2;
    unsigned *arr3;

    arr1 = (unsigned ***)malloc(n * sizeof(unsigned **));
    arr2 = (unsigned **)malloc(n * m * sizeof(unsigned *));
    arr3 = (unsigned *)malloc(n * m * k * sizeof(unsigned));

    for (int i = 0; i < n; ++i)
    {
        arr1[i] = arr2 + (i * m);
        for (int j = 0; j < m; ++j)
        {
            arr1[i][j] = arr3 + j * k;
        }
        arr3 += m * k;
    }

    return arr1;
}

void delete_3d_array(unsigned ***arr)
{
    free(**arr);
    free(*arr);
    free(arr);
}