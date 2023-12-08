#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    int number, age;
    struct _Node *prev;
    struct _Node *next;
} Node;

int cmp(const void *a, const void *b);

Node *ptr_arr[500001];
Node *createList(int n);
Node *solve(int n, int m);

Node *createList(int n)
{
    Node *head = malloc(n * sizeof(Node));
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &(head[i].age));
        head[i].number = i + 1;
        ptr_arr[i] = &head[i];

        if (i == n - 1)
            head[i].next = &head[0];
        else
            head[i].next = &head[i + 1];

        if (i == 0)
            head[i].prev = &head[n - 1];
        else
            head[i].prev = &head[i - 1];
    }
    qsort(ptr_arr, n, sizeof(ptr_arr[0]), cmp);

    return head;
}

Node *solve(int n, int m)
{
    int a, k;
    char dir;

    for (int i = 0; i < m; ++i)
    {
        scanf("%d %d %c", &a, &k, &dir);
        a--;
        k %= (n - 1);
        if (k == 0)
            continue;

        Node *cur = ptr_arr[a];
        Node *prev = cur->prev;
        Node *next = cur->next;

        prev->next = next;
        next->prev = prev;

        if (dir == 'R')
        {
            while (k--)
            {
                next = next->next;
                prev = prev->next;
            }
        }
        else if (dir == 'L')
        {
            while (k--)
            {
                next = next->prev;
                prev = prev->prev;
            }
        }

        prev->next = cur;
        cur->prev = prev;
        cur->next = next;
        next->prev = cur;
    }

    return ptr_arr[0];
}

int cmp(const void *a, const void *b)
{
    Node *i = *(Node **)a;
    Node *j = *(Node **)b;
    if (i->age != j->age)
        return i->age - j->age;
    else
        return i->number - j->number;
}