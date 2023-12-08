#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    int data;
    struct _Node *next;
} Node;

void printList(Node *head);
void freeList(Node *head);
void deleteNode(Node **nd, int data);
Node *createList();

int main()
{
    // freopen("test.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);

    Node *head;
    int data;

    head = createList();

    while (1)
    {
        scanf("%d", &data);
        if (data > -1)
        {
            deleteNode(&head, data);
        }
        else
        {
            break;
        }
    }

    printList(head);
    freeList(head);
    return 0;
}

Node *createList()
{
    int data;
    Node *head, *cur;

    scanf("%d", &data);
    if (data == -1)
        return NULL;
    else
    {
        head = cur = malloc(sizeof(Node));
        cur->data = data;
    }

    while (1)
    {
        scanf("%d", &data);
        if (data > -1)
        {
            Node *new = malloc(sizeof(Node));
            new->data = data;
            cur->next = new;
            cur = new;
        }
        else
        {
            cur->next = NULL;
            break;
        }
    }
    return head;
}

void deleteNode(Node **nd, int data)
{
    Node *tmp;
    Node *prev = *nd;
    int i;

    if (data == 1)
    {
        Node *dele = *nd;
        *nd = (*nd)->next;
        free(dele);
        return;
    }

    for (tmp = *nd, i = 1; tmp != NULL; tmp = tmp->next, ++i)
    {
        if (i == data)
        {
            Node *dele = tmp;
            prev->next = tmp->next;
            free(dele);
            break;
        }
        prev = tmp;
    }
}

void printList(Node *head)
{
    Node *temp;
    for (temp = head; temp != NULL; temp = temp->next)
    {
        printf("%d ", temp->data);
    }
}

void freeList(Node *head)
{
    Node *temp;
    for (temp = head; temp != NULL; temp = head)
    {
        head = head->next;
        free(temp);
    }
}
