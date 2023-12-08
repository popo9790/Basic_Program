#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long int lli;

typedef struct _Node
{
    char data;
    struct _Node *left, *right;
} Node;

Node *func_arr[26];
int pos = 0, len;
int state_arr[5];
char expr[250];

Node *Create_Node(char data);
Node *Create_Tree();
lli Calculation(Node *root);
lli Mod(lli num);
void Free_Node(Node *root);

int main(void)
{
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; ++i)
    {
        char func;
        scanf(" %c ", &func);
        scanf("%s", expr);

        pos = 0;
        len = strlen(expr);
        func_arr[func - 'a'] = Create_Tree();
    }
    while (q--)
    {
        char func;
        scanf(" %c ", &func);
        for (int i = 0; i < 5; ++i)
            scanf("%d", &state_arr[i]);
        lli ans = Calculation(func_arr[func - 'a']);
        printf("%lld\n", ans);
    }
    for (int i = 0; i < 26; ++i)
        Free_Node(func_arr[i]);
}

Node *Create_Node(char data)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node *Create_Tree()
{
    char c;
    Node *root;
    if (pos < len)
    {
        c = expr[pos++];
        root = Create_Node(c);
        if (c == '+' || c == '*' || c == '@')
        {
            root->left = Create_Tree();
            root->right = Create_Tree();
        }
        else if (c == '-')
        {
            root->right = Create_Tree();
        }
    }
    return root;
}

lli Calculation(Node *root)
{
    lli ans = 0;
    if (root)
    {
        char data = root->data;
        lli l = Calculation(root->left);
        lli r = Calculation(root->right);
        if (data == '+')
            return ans = Mod(l + r);
        else if (data == '-')
            return ans = Mod(r * (-1));
        // return ans = Mod(l - r);
        else if (data == '*')
            return ans = Mod(l * r);
        else if (data == '@')
        {
            char func = (root->left->data);
            int origin_x = state_arr[0];
            state_arr[0] = r;
            ans = Mod(Calculation(func_arr[func - 'a']));
            state_arr[0] = origin_x;
            return ans;
        }
        else if (data >= 'A' && data <= 'D')
            return ans = Mod(state_arr[data - 'A' + 1]); // remember to plus 1
        else if (data == 'X')
            return ans = Mod(state_arr[0]);
    }
    return ans;
}

lli Mod(lli num)
{
    num %= 998244353;
    if (num < 0)
        num += 998244353;
    return num;
}

void Free_Node(Node *root)
{
    if (root)
    {
        Free_Node(root->left);
        Free_Node(root->right);
        free(root);
    }
}