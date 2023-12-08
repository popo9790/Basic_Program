#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode
{
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

void printInfix(Node *root);
void constructTree(Node **head);
void freeTree(Node *root);

int main(void)
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    int n;

    scanf("%d", &n); // the number of test cases
    while (n > 0)
    {
        getchar();
        Node *root = NULL;
        constructTree(&root); // construct syntax tree
        printInfix(root);     // you have to implement this function
        printf("\n");
        freeTree(root);
        --n;
    }

    return 0;
}

void printInfix(Node *root)
{
    if (root)
    {
        printInfix(root->left);
        putchar(root->data);
        if (root->right)
        {
            if ((root->right)->data == '|' || (root->right)->data == '&')
                putchar('(');
            printInfix(root->right);
            if ((root->right)->data == '|' || (root->right)->data == '&')
                putchar(')');
        }
    }
}

void constructTree(Node **head)
{
    char c;

    if ((*head) == NULL)
    {
        (*head) = (Node *)malloc(sizeof(Node));
        c = getchar();

        (*head)->data = c;

        (*head)->left = (*head)->right = NULL;

        if ((*head)->left == NULL && ((*head)->data == '&' || (*head)->data == '|'))
            constructTree(&(*head)->left);
        if ((*head)->right == NULL && ((*head)->data == '&' || (*head)->data == '|'))
            constructTree(&(*head)->right);
    }
}

void freeTree(Node *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}