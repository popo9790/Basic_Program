#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int value;
    struct _node *left;
    struct _node *right;
} Node;

int n;
int pos;
int post_index;

Node *Create_Node(int value);
Node *Build(int *inorder, int *preorder, int inorder_start, int inorder_end);
int Verify(Node *root, int *postorder);
void Destroy(Node *root);

int main(void)
{
    Node *head;
    int t;

    scanf("%d", &n);
    int pre[n + 1];  // root -> left -> right
    int post[n + 1]; // left -> right -> root
    int in[n + 1];   // left -> root -> right

    for (int i = 0; i < n; ++i)
        scanf("%d", &pre[i]);
    for (int i = 0; i < n; ++i)
        scanf("%d", &post[i]);

    scanf("%d", &t);
    for (int j = 0; j < t; ++j)
    {
        pos = post_index = 0; // 初始化
        for (int i = 0; i < n; ++i)
            scanf("%d", &in[i]);
        head = Build(in, pre, 0, n - 1); // n-1超級重要！！！ 因為要丟進去的是index
        printf("%s\n", Verify(head, post) ? "Yes" : "No");
        Destroy(head);
    }
}

Node *Create_Node(int value)
{
    Node *New_Node = malloc(sizeof(Node));

    New_Node->value = value;
    New_Node->left = NULL;
    New_Node->right = NULL;

    return New_Node;
}

Node *Build(int *inorder, int *preorder, int inorder_start, int inorder_end)
{
    Node *root = NULL;
    if (inorder_start <= inorder_end && pos < n) // = 發生在剩下一個點的時候
    {
        root = Create_Node(preorder[pos++]);

        int root_index = 0;
        for (root_index = inorder_start; root_index <= inorder_end; ++root_index)
            if (inorder[root_index] == root->value)
                break;

        root->left = Build(inorder, preorder, inorder_start, root_index - 1); // root的前半段
        root->right = Build(inorder, preorder, root_index + 1, inorder_end);  // root的後半段
    }
    return root;
}

int Verify(Node *root, int *postorder)
{
    int ans = 1; // It is important to assign ans = 1, since 1 in [and]gate is non-contraling bit;
    if (root != NULL)
    {
        ans *= Verify(root->left, postorder);
        ans *= Verify(root->right, postorder);
        if (root->value != postorder[post_index++])
            ans = 0;
    }
    return ans;
}

void Destroy(Node *root)
{
    if (root != NULL)
    {
        Destroy(root->left);
        Destroy(root->right);
        free(root);
    }
}
