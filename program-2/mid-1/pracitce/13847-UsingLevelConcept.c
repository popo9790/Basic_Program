#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int idx, level, left, right;
} Node;

Node arr[3001];
int inorder[3001];
int op[1505][2];
int Root, N, count = 0;

void add_node(int root, int root_idx, int start, int end);
void print_tree(int root);

int main()
{
    scanf("%d", &N);

    // record the inorder_idx of each node
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &inorder[i]);
        arr[inorder[i]].idx = i;
    }

    // record the level of node and count the Root
    int sum = N * (N + 1) / 2;
    for (int i = 0; i < (N - 1) / 2; i++)
    {
        scanf("%d %d", &op[i][0], &op[i][1]);
        arr[op[i][0]].level = arr[op[i][1]].level = i;
        sum -= op[i][0] + op[i][1];
    }
    Root = sum;

    // construct the tree
    add_node(Root, arr[Root].idx, 0, N);

    // output
    print_tree(Root);
}

void add_node(int root, int root_idx, int start, int end)
{
    if (!root)
        return;

    // search the nodes with same level but in different interval
    int flag = 1;
    for (int i = start; i < root_idx && flag; i++)
    {
        for (int j = root_idx + 1; j < end && flag; j++)
        {
            if (arr[inorder[i]].level == arr[inorder[j]].level)
            {
                arr[root].left = inorder[i];
                arr[root].right = inorder[j];
                flag = 0;
            }
        }
    }

    add_node(arr[root].left, arr[arr[root].left].idx, start, root_idx);
    add_node(arr[root].right, arr[arr[root].right].idx, root_idx + 1, end);
}

void print_tree(int root)
{
    printf("%d", root);
    count++;
    count == N ? printf("\n") : printf(" ");
    if (arr[root].left)
        print_tree(arr[root].left);
    if (arr[root].right)
        print_tree(arr[root].right);
}
