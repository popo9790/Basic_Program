#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    int id;
    struct _Node *next;
} Node;

void reverse(Node *node_l, Node *node_r);

void reverse(Node *node_l, Node *node_r)
{
    Node *head = node_l->next;
    Node *end = node_r->next;

    Node *prev = head;
    for (Node *cur = head->next; cur != end;)
    {
        Node *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    head->next = end;
    node_l->next = node_r;
}