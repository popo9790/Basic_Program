#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXEXPR 256
#define NUMSYM 6

char expr[MAXEXPR]; // string to store the input expression.
int pos;            // current position of parsing, from end to start

typedef enum
{
    ID_A,
    ID_B,
    ID_C,
    ID_D,
    OP_AND,
    OP_OR
} TokenSet;
char sym[NUMSYM];

typedef struct _Node
{
    TokenSet data;
    struct _Node *left, *right;
} BTNode;

BTNode *EXPR();
BTNode *FACTOR();
BTNode *makeNode(char c);
void freeTree(BTNode *root);
void printPrefix(BTNode *root);

BTNode *makeNode(char c)
{
    BTNode *New_Node = malloc(sizeof(BTNode));
    for (int i = 0; i < NUMSYM; ++i)
    {
        if (c == sym[i])
        {
            New_Node->data = i;
            break;
        }
    }
    New_Node->left = NULL;
    New_Node->right = NULL;

    return New_Node;
}

BTNode *EXPR()
{
    char c;
    BTNode *root = NULL;
    BTNode *right = NULL;
    if (pos >= 0)
    {
        right = FACTOR();
        if (pos > 0)
        {
            c = expr[pos];
            if (c == '|' || c == '&')
            {
                root = makeNode(c);
                root->right = right;
                pos--; // 重要
                root->left = EXPR();
            }
            else
                root = right; // 如果不是OP的話
        }
        else
            root = right; // pos 跑到0的時候
    }
    return root;
}

BTNode *FACTOR()
{
    char c;
    BTNode *root = NULL;

    if (pos >= 0)
    {
        c = expr[pos--];
        if (c >= 'A' && c <= 'D')
            root = makeNode(c);
        else if (c == ')')
        {
            root = EXPR();
            if (expr[pos--] != '(') // It is important cuz you need to discars the (
                freeTree(root);
        }
    }
    return root;
}

#endif