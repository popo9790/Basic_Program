#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node
{
    char data;
    struct _Node *left, *right;
} BTNode;

int pos, l;
char expr[230];

BTNode *Create_Node(char c);
BTNode *Create_Tree();
void Show_Tree(BTNode *node);
void Free_Node(BTNode *node);

int main(void)
{
    BTNode *head;

    scanf("%s", expr);
    l = strlen(expr);
    head = Create_Tree();
    Show_Tree(head);
    Free_Node(head);
    puts("");
}

BTNode *Create_Node(char c)
{
    BTNode *new = malloc(sizeof(BTNode));
    new->data = c;
    new->left = NULL;
    new->right = NULL;
    return new;
}

BTNode *Create_Tree()
{
    char c;
    BTNode *node = NULL;
    if (pos < l)
    {
        c = expr[pos++];
        node = Create_Node(c); // 因為題目給我的是prefix, 代表他每一個頭都是一個root
        if (!(c >= 'A' && c <= 'Z'))
        {
            node->left = Create_Tree();
            node->right = Create_Tree();
        }
    }
    return node;
}

void Show_Tree(BTNode *node)
{
    if (node)
    {
        BTNode *right = node->right;
        BTNode *left = node->left;
        char c = node->data;
        if (left)
        {
            if ((c == '*' || c == '/') && (left->data == '+' || left->data == '-'))
            {
                putchar('(');
                Show_Tree(left);
                putchar(')');
            }
            else
                Show_Tree(left);
        }
        putchar(c);
        if (right)
        {
            if ((c == '-' || c == '*') && (right->data == '+' || right->data == '-'))
            {
                putchar('(');
                Show_Tree(right);
                putchar(')');
            }
            else if (c == '/' && (right->data == '+' || right->data == '-' || right->data == '*' || right->data == '/'))
            {
                putchar('(');
                Show_Tree(right);
                putchar(')');
            }
            else
                Show_Tree(right);
        }
    }
}

void Free_Node(BTNode *node)
{
    if (node != NULL)
    {
        Free_Node(node->left);
        Free_Node(node->right);
        free(node);
    }
}