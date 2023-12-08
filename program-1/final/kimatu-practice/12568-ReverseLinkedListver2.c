#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node
{
    int data;
    struct _Node *next;
} Node;

void Print_List(Node *head);
void Delete_List(Node *head);

void Push(Node **ptr_head, int x);
void Pop(Node **ptr_head);
void Reverse_List(Node **ptr_head);

int main()
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    char op[10];
    Node *head = NULL;
    while (~scanf("%s", op))
    {
        if (strcmp(op, "push") == 0)
        {
            int x;
            scanf("%d", &x);
            Push(&head, x);
        }
        if (strcmp(op, "pop") == 0)
        {
            Pop(&head);
        }
        if (strcmp(op, "reverse") == 0)
        {
            Reverse_List(&head);
        }
        if (strcmp(op, "print") == 0)
        {
            Print_List(head);
        }
    }

    Delete_List(head);
    head = NULL;

    return 0;
}

void Print_List(Node *head)
{
    if (head == NULL)
    {
        printf("\n");
        return;
    }
    printf("%d", head->data);
    if (head->next != NULL)
        printf(" -> ");
    Print_List(head->next);
}

void Delete_List(Node *head)
{
    if (head == NULL)
        return;
    Delete_List(head->next);
    free(head);
}

void Push(Node **ptr_head, int x)
{
    Node *newnode = (Node *)malloc(sizeof(Node));

    newnode->data = x;
    newnode->next = *ptr_head;

    *ptr_head = newnode;
}

void Pop(Node **ptr_head)
{
    if (*ptr_head != NULL)
    {
        Node *dontuse = *ptr_head;
        *ptr_head = (*ptr_head)->next;
        free(dontuse);
    }
}

void Reverse_List(Node **ptr_head)
{
    Node *cur = *ptr_head;
    Node *pre = NULL;
    Node *next = NULL;

    while (cur != NULL)
    {
        next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = next;
    }
    *ptr_head = pre;
}