#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *left;
    struct node *right;
} Node;

Node *head = NULL;
int Inorder[3005];
int pos[3005];
int level[3005];
int idx = 0, n;

Node *makeNode(int data);
Node *createTree(int start, int end, int root_index);
void Show(Node *root);

int main(void)
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &Inorder[i]);
        pos[Inorder[i]] = i;
    }

    int sum = n * (n + 1) / 2, root_index;
    for (int i = 0; i < (n - 1) / 2; ++i)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        level[a] = level[b] = i;
        sum -= a + b;
    }
    root_index = pos[sum];
    head = createTree(0, n - 1, root_index); // 丟index進去
    Show(head);
}

Node *makeNode(int data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *createTree(int start, int end, int root_index)
{
    Node *root = makeNode(Inorder[root_index]);
    if (start <= end)
    {
        for (int i = start; i < root_index; ++i)
            for (int j = root_index + 1; j <= end; ++j)
                if (level[Inorder[i]] == level[Inorder[j]])
                {
                    root->left = createTree(start, root_index - 1, pos[Inorder[i]]);
                    root->right = createTree(root_index + 1, end, pos[Inorder[j]]);
                    break;
                }
    }
    return root;
}

void Show(Node *root)
{
    if (root)
    {
        idx++; // print \n
        printf("%d%c", root->data, " \n"[idx == n]);
        Show(root->left);
        Show(root->right);
    }
}