#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    char c;
    struct _Node *prev;
    struct _Node *next;
} Node;

int size;
char *input;
Node *dummy_node;

void Create_Node(Node **cursor, char c);
void Delete_Node(Node **cursor);
void Show_Node(Node *head);
void Free_Node(Node *head);

int main(void)
{
    dummy_node = malloc(sizeof(Node));

    int n;
    scanf("%d", &n);
    while (n--)
    {
        Node *cursor = dummy_node;
        dummy_node->next = NULL;
        dummy_node->prev = NULL;

        scanf("%d", &size);
        input = malloc((size + 1) * sizeof(char));
        scanf("%s", input);
        for (int i = 0; i < size; ++i)
        {
            if (input[i] == 'L')
            {
                cursor = cursor->prev;
            }
            else if (input[i] == 'R')
            {
                cursor = cursor->next;
            }
            else if (input[i] == 'B')
            {
                Delete_Node(&cursor);
            }
            else
                Create_Node(&cursor, input[i]);
        }
        Show_Node(dummy_node);
        Free_Node(dummy_node);
    }
    free(dummy_node);
}

void Create_Node(Node **cursor, char c)
{
    Node *new = malloc(sizeof(Node));
    new->c = c;
    if ((*cursor)->next == NULL)
    {
        (*cursor)->next = new;
        new->prev = *cursor;
        new->next = NULL;
    }
    else
    {
        Node *next = (*cursor)->next;

        next->prev = new;
        new->next = next;
        new->prev = *cursor;
        (*cursor)->next = new;
    }
    *cursor = new;
}

void Delete_Node(Node **cursor)
{
    Node *dele = *cursor;
    Node *next = (*cursor)->next;
    Node *prev = (*cursor)->prev;

    prev->next = next;
    if (next != NULL)
        next->prev = prev;
    *cursor = prev;

    free(dele);
}

void Show_Node(Node *head)
{
    for (Node *cursor = head->next; cursor != NULL; cursor = cursor->next)
        putchar(cursor->c);
    puts("");
}

void Free_Node(Node *head)
{
    for (Node *cursor = head->next; cursor != NULL;)
    {
        Node *next = cursor->next;
        free(cursor);
        cursor = next;
    }
    free(input);
}