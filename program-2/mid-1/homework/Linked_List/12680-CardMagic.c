#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    int size;
    int *data;
    struct _Node *next;
} Node;

Node *ReadOneList();
void PrintList(Node *tmp);
void Merge(Node *tmp, int from, int to);
void Cut(Node *tmp, int from, int num);

Node *ReadOneList()
{
    Node *new = malloc(sizeof(Node));
    scanf("%d:", &new->size);
    new->data = malloc((new->size) * sizeof(int));
    new->next = NULL;
    for (int i = 0; i < new->size; ++i)
        scanf("%d", &(new->data)[i]);

    return new;
}

void Merge(Node *tmp, int from, int to)
{
    Node *FrNode;
    Node *FrPrev;
    Node *ToNode;

    int cnt = 0;
    for (Node *cur = tmp; cur != NULL; cur = cur->next, cnt++)
    {
        if (cnt == from)
            FrNode = cur;
        if (cnt == from - 1)
            FrPrev = cur;
        if (cnt == to)
            ToNode = cur;
    }

    int NewSize = FrNode->size + ToNode->size;
    int *new = malloc(NewSize * sizeof(Node));
    for (int i = 0; i < ToNode->size; ++i)
        new[i] = (ToNode->data)[i];
    for (int i = ToNode->size; i < NewSize; ++i)
        new[i] = (FrNode->data)[i - ToNode->size];

    free(ToNode->data);
    ToNode->data = new;
    ToNode->size = NewSize;

    FrPrev->next = FrNode->next;
    free(FrNode->data);
    free(FrNode);
}

void Cut(Node *tmp, int from, int num)
{
    Node *FrNode;

    int cnt = 0;
    for (Node *cur = tmp; cur != NULL; cur = cur->next, cnt++)
        if (cnt == from)
            FrNode = cur;

    Node *new_node = malloc(sizeof(Node));
    new_node->size = FrNode->size - num;
    new_node->data = malloc((new_node->size) * sizeof(int));
    for (int i = 0; i < new_node->size; ++i)
        (new_node->data)[i] = (FrNode->data)[num + i];

    FrNode->size = num;
    int *new_arr = malloc(FrNode->size * sizeof(int));
    for (int i = 0; i < FrNode->size; ++i)
        (new_arr)[i] = (FrNode->data)[i];
    free(FrNode->data);
    FrNode->data = new_arr;

    new_node->next = FrNode->next;
    FrNode->next = new_node;
}

void PrintList(Node *tmp)
{
    for (Node *cur = tmp->next; cur != NULL; cur = cur->next)
        for (int i = 0; i < cur->size; ++i)
            printf("%d%c", (cur->data)[i], " \n"[i == cur->size - 1]);
}