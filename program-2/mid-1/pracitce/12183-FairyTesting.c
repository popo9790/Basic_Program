#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int value; // This is the value of the subtree, not the ID number
    int token;
    struct node *left;
    struct node *right;
    struct node *parent; // pointing to the parent node
} Node;

Node *variable[100001];
int pos, len;
char expr[1000001];

Node *createNode(Node *parent, int id);
Node *createTree(Node *parent);
int evaluate();
void calculation(Node *root);
void freeNode(Node *root);

int main(void)
{
    Node *head = NULL;
    int t, n, m;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d %d", &n, &m);
        scanf("%s", expr);

        len = strlen(expr);
        pos = 0;

        head = createTree(NULL);
        for (int i = 0; i < m; ++i)
        {
            int flip;
            scanf("%d", &flip);
            variable[flip]->value = !variable[flip]->value;
            calculation(variable[flip]);
            printf("%d\n", head->value);
        }
        freeNode(head);
        head = NULL;
    }
}

Node *createNode(Node *parent, int id)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = parent;
    newNode->value = 0;
    newNode->token = id;
    return newNode;
}

Node *createTree(Node *parent)
{
    Node *root = NULL;
    char c;
    if (pos < len)
    {
        c = expr[pos++];
        switch (c)
        {
        case '|':
        case '&':
            if (c == '|')
                root = createNode(parent, -1);
            else
                root = createNode(parent, -2);
            root->left = createTree(root);
            root->right = createTree(root);
            break;
        case '[':
            root = createNode(parent, evaluate());
            variable[root->token] = root; // 重要！！
            break;
        }
    }
    return root;
}

int evaluate()
{
    int index = 0;
    char str[100001];
    char c;
    while (1)
    {
        c = expr[pos++];
        if (c == ']')
            break;
        str[index++] = c;
    }
    str[index] = '\0';
    return atoi(str);
}

void calculation(Node *root)
{
    if (root)
    {
        Node *parent = root->parent;
        if (parent)
        {
            int origin = parent->value;
            int count = 0;
            if (parent->token == -1) // OR
                count = parent->left->value + parent->right->value;
            else if (parent->token == -2) // AND
                count = parent->left->value * parent->right->value;

            if (count > 0)
                count = 1;
            if (origin != count)
            {
                parent->value = count;
                calculation(parent);
            }
        }
    }
}

void freeNode(Node *root)
{
    if (root)
    {
        freeNode(root->left);
        freeNode(root->right);
        free(root);
    }
}