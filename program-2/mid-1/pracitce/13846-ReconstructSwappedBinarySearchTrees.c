#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node
{
    int data;
    struct _Node *left, *right;
} Node;

int n;
int Preorder[100005];

Node *createNode(int data);
void insertNode(Node *root, int data);
void Show(Node *root);

int main(void)
{
    Node *head;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", &Preorder[i]);

    head = createNode(Preorder[0]);
    for (int i = 1; i < n; ++i)
        insertNode(head, Preorder[i]);
    Show(head);
}

Node *createNode(int data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insertNode(Node *root, int data)
{
    if (data > root->data)
    {
        if (root->right == NULL)
            root->right = createNode(data);
        else
            insertNode(root->right, data);
    }
    else
    {
        if (root->left == NULL)
            root->left = createNode(data);
        else
            insertNode(root->left, data);
    }
}

void Show(Node *root)
{
    if (root)
    {
        Show(root->left);
        Show(root->right);
        printf("%d%c", root->data, " \n"[root->data == Preorder[0]]);
    }
}
