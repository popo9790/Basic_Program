#include <stdio.h>
#include <string.h>

int main()
{
    // freopen("test.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int t;
    scanf(" %d", &t);
    while (t-- != 0)
    {

        char a[2001], b[2001];
        int q;

        scanf("%s %s", a, b);
        scanf("%d", &q);

        int lenthb = strlen(b), lentha = strlen(a);
        int subarr[lenthb][lentha];
        for (int i = 0; i < lenthb; i++)
        {
            memset(subarr[i], 0, lentha);
        }
        for (int i = 0; i < lentha; ++i)
        {
            for (int j = 0; j < lenthb; ++j)
            {
                if (i + j < lentha && b[j] == a[i + j])
                {
                    subarr[j][i] = 1;
                }
                else
                {
                    break;
                }
            }
        }

        while (q--)
        {
            int l, r, count = 1;

            scanf("%d %d", &l, &r);
            int diff = r - l + 1;

            if (diff > lenthb)
            {
                diff = lenthb;
            }

            for (int i = 0; i < diff; ++i)
            {
                count += subarr[i][r - i];
            }

            printf("%d\n", count);
        }
    }

    return 0;
}
