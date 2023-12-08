#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node
{
    int data;
    struct _Node *parent, *left, *right;
} BTNode;

int n, flag = 0, pos = 0; // pos is index for route
int visited[3005];
char route[3005];
BTNode *ptr_arr[3005];

void Create_Node();
void init();
void Find_Node(int Fr, int To);
void Show();

int main(void)
{
    scanf("%d", &n);
    Create_Node();

    for (int i = 1; i <= n; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        ptr_arr[i]->left = ptr_arr[a];
        ptr_arr[i]->right = ptr_arr[b];
        if (a != 0)
            ptr_arr[a]->parent = ptr_arr[i];
        if (b != 0)
            ptr_arr[b]->parent = ptr_arr[i];
    }

    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        int a, b;
        init();
        scanf("%d %d", &a, &b);
        Find_Node(a, b);
    }

    for (int i = 1; i <= n; ++i)
        free(ptr_arr[i]);
}

void Create_Node()
{
    visited[0] = 1;
    ptr_arr[0] = NULL;
    for (int i = 1; i <= n; ++i)
    {
        BTNode *new = malloc(sizeof(BTNode));
        new->data = i;
        new->parent = NULL;
        new->left = NULL;
        new->right = NULL;
        ptr_arr[i] = new;
    }
}

void init()
{
    flag = 0;
    pos = 0;
    memset(visited, 0, sizeof(visited));
    memset(route, 0, sizeof(route));
}

void Find_Node(int Fr, int To)
{
    int next;
    if (flag)
        return;

    if (Fr == To)
    {
        puts(route);
        flag = 1;
        return;
    }

    if (ptr_arr[Fr]->left)
    {
        next = (ptr_arr[Fr]->left)->data;
        if (visited[next] == 0)
        {
            visited[Fr] = 1;
            route[pos++] = 'L';
            Find_Node(next, To);
            route[--pos] = '\0'; // it is important to --pos
        }
    }

    if (ptr_arr[Fr]->right)
    {
        next = (ptr_arr[Fr]->right)->data;
        if (visited[next] == 0)
        {
            visited[Fr] = 1;
            route[pos++] = 'R';
            Find_Node(next, To);
            route[--pos] = '\0';
        }
    }

    if (ptr_arr[Fr]->parent)
    {
        next = (ptr_arr[Fr]->parent)->data;
        if (visited[next] == 0)
        {
            visited[Fr] = 1;
            route[pos++] = 'P';
            Find_Node(next, To);
            route[--pos] = '\0';
        }
    }
}