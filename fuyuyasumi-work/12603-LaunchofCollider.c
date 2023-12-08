#include <stdio.h>
#include <stdlib.h>

#define N 2000005

int main(void)
{
    int n;
    int min_pos = __INT32_MAX__;
    int position[N];
    char dir[N];

    scanf("%d", &n);
    scanf("%s", dir);
    for (int i = 0; i < n; ++i)
        scanf("%d", &position[i]);

    for (int i = 0; i < n - 1; ++i)
        if (dir[i] == 'R' && dir[i + 1] == 'L')
            if (abs(position[i] - position[i + 1]) < min_pos)
                min_pos = abs(position[i] - position[i + 1]);

    if (min_pos != __INT32_MAX__)
        printf("%d\n", min_pos / 2);
    else
        printf("-1\n");
}