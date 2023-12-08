#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000
#define MAX_LEN 100

typedef struct
{
    int score;
    char *name;
} Node;

// Node* Table[MAX_SIZE];
// N = number of nodes in Table

void Insert(Node **Table, int N, int score, char *name);
void Delete(Node **Table, int N, char *name);
int *Top(Node **Table, int N, int x);
static int check(const void *i, const void *j);

int N = 0;
Node *Table[MAX_SIZE];

int main()
{
    freopen("test.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    for (int i = 0; i < MAX_SIZE; i++)
        Table[i] = NULL;

    int K;
    scanf("%d", &K);

    char op[10];

    while (K--)
    {
        // printf("K: %d\n", K);
        scanf("%s", op);
        if (strcmp(op, "INSERT") == 0)
        {
            int score;
            char name[MAX_LEN + 1];
            scanf("%d %s", &score, name);

            Insert(Table, N, score, name);
            N++;
        }
        else if (strcmp(op, "DELETE") == 0)
        {
            char name[MAX_LEN + 1];
            scanf("%s", name);

            Delete(Table, N, name);
            N--;
        }
        else if (strcmp(op, "TOP") == 0)
        {
            int x;
            scanf("%d", &x);

            int *idxs = Top(Table, N, x);
            printf("Top %d:\n", x);
            for (int i = 0; i < x; i++)
            {
                printf("%d %s\n", Table[idxs[i]]->score, Table[idxs[i]]->name);
            }
            free(idxs);
        }
    }
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (Table[i] != NULL)
        {
            free(Table[i]->name);
            free(Table[i]);
            Table[i] = NULL;
        }
    }

    return 0;
}

void Insert(Node **Table, int N, int score, char *name)
{
    Table[N] = (Node *)malloc(sizeof(Node));
    Table[N]->name = (char *)malloc((strlen(name) + 1) * sizeof(char));

    strcpy(Table[N]->name, name);
    Table[N]->score = score;
}

void Delete(Node **Table, int N, char *name)
{
    for (int i = 0; i < N; ++i)
    {
        if (strcmp(Table[i]->name, name) == 0)
        {
            free(Table[i]->name);
            free(Table[i]);
            for (int j = i; j < N - 1; ++j)
            {
                Table[j] = Table[j + 1];
            }
            Table[N - 1] = NULL; // 重要
            break;
        }
    }
}

int *Top(Node **Table, int N, int x)
{
    int *index = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; ++i)
    {
        index[i] = i;
    }

    qsort(index, N, sizeof(index[0]), check);

    return index;
}

static int check(const void *i, const void *j)
{
    int a = *(int *)i;
    int b = *(int *)j;

    if (Table[a]->score < Table[b]->score)
    {
        return 1;
    }
    else if (Table[a]->score == Table[b]->score)
    {
        if (strcmp(Table[a]->name, Table[b]->name) > 0)
        {
            return 1;
        }
    }

    return 0;
}