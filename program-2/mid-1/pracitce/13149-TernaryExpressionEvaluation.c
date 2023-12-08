#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node
{
    int index;
    struct _Node *left, *right;
} Node;

int flag = 0;
char val[3005];
char ch_var[3005];

Node *createNode(int index);
Node *createTree();
void Calculation(Node *root);

int main(void)
{
    Node *head;
    int n;

    head = createTree();
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
    {
        flag = 0;
        scanf("%s", val);
        Calculation(head);
    }
}

Node *createNode(int index)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->index = index;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *createTree()
{
    Node *root = NULL;
    char c;
    int pos = 0;
    while ((c = getchar()))
    {
        if (c == ':' || c == '?' || c == '\n')
            break;
        ch_var[pos++] = c;
    }
    ch_var[pos] = '\0';

    root = createNode(atoi(ch_var));
    if (c == '?')
    {
        root->left = createTree();
        root->right = createTree();
    }
    return root;
}

void Calculation(Node *root)
{
    if (flag)
        return;
    if (root)
    {
        if (root->left == NULL && root->right == NULL) // 到最後了
        {
            flag = 1;
            printf("%d\n", val[root->index - 1] - '0');
        }
        if (val[root->index - 1] - '0')
            Calculation(root->left); // true to left
        else
            Calculation(root->right); // false to right
    }
}