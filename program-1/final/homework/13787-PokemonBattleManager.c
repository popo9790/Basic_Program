#include <stdio.h>
#include <string.h>

#define lvup_atk 200
#define lvup_dfn 100
#define lvup_maxHp 20
#define lvup_maxMp 15
#define T 2

typedef struct
{
    int id;
    char name[10];
    int level;
    int attack;
    int defense;
    int Hp;
    int Mp;
    int maxHp;
    int maxMp;
    int costMp;
} Pokemon;

char thename[10][100] = {"Geodude", "Raichu", "Golbat", "Magnemite", "Exeggutor"};

int max(int a, int b);
void level_up(Pokemon *P);
void battle(Pokemon *A, Pokemon *B);
void init();
void init_pokemon(int idx, int atk, int dfn, int hp, int mp, int cmp);

Pokemon myPokemon[1005];
Pokemon initPokemon[10];

int main()
{
    freopen("test.txt", "r", stdin);
    freopen("out.txt", "w", stdout);

    init();
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int type;
        scanf("%d", &type);
        myPokemon[i] = initPokemon[type];
    }

    int t;
    scanf("%d", &t);
    while (t--)
    {
        int c;
        scanf("%d", &c);
        if (c == 1)
        {
            int a;
            scanf("%d", &a);
            level_up(&myPokemon[a]);
        }
        else
        {
            int a, b;
            scanf("%d%d", &a, &b);
            battle(&myPokemon[a], &myPokemon[b]);
        }
    }
    return 0;
}

void init()
{
    init_pokemon(0, 300, 100, 10, 20, 5);
    init_pokemon(1, 400, 50, 10, 25, 10);
    init_pokemon(2, 200, 80, 10, 15, 3);
    init_pokemon(3, 200, 50, 10, 15, 4);
    init_pokemon(4, 500, 150, 15, 20, 10);
}

void init_pokemon(int idx, int atk, int dfn, int hp, int mp, int cmp)
{
    strcpy(initPokemon[idx].name, thename[idx]);
    initPokemon[idx].id = idx;
    initPokemon[idx].level = 1;
    initPokemon[idx].attack = atk;
    initPokemon[idx].defense = dfn;
    initPokemon[idx].Hp = hp;
    initPokemon[idx].Mp = mp;
    initPokemon[idx].maxHp = hp;
    initPokemon[idx].maxMp = mp;
    initPokemon[idx].costMp = cmp;
}

void level_up(Pokemon *P)
{
    if (P->level < 5)
    {
        P->level++;
        P->attack += lvup_atk;
        P->defense += lvup_dfn;
        P->maxHp += lvup_maxHp;
        P->maxMp += lvup_maxMp;

        P->Hp = P->maxHp;
        P->Mp = P->maxMp;
    }
}

void battle(Pokemon *A, Pokemon *B)
{
    if (A->Hp == 0 && B->Hp == 0)
    {
        puts("Draw.\n");
        puts("");
        return;
    }
    else if (A->Hp == 0)
    {
        printf("%s is the winner! %s died in vain...\n", B->name, A->name);
        puts("");
        return;
    }
    else if (B->Hp == 0)
    {
        printf("%s is the winner! %s died in vain...\n", A->name, B->name);
        puts("");
        return;
    }

    while (1)
    {
        int Dam = 0;

        A->Mp += T;
        if (A->Mp > A->maxMp)
            A->Mp = A->maxMp;

        if (A->Mp >= A->costMp)
        {
            A->Mp -= A->costMp;
            Dam = 2 * A->level * max(A->attack - B->defense, 0) / 100;
            B->Hp -= Dam;

            if (B->Hp <= 0)
            {
                B->Hp = 0;
                printf("%s used Headbutt!\n", A->name);
                printf("%s now has %d HP.\n", B->name, B->Hp);
                printf("%s is the winner! %s died in vain...\n", A->name, B->name);
                puts("");
                return;
            }
            printf("%s used Headbutt!\n%s now has %d HP.\n", A->name, B->name, B->Hp);
        }
        else
        {
            A->Mp += T;
            printf("%s used Rest!\n%s now has %d MP.\n", A->name, A->name, A->Mp);
        }

        B->Mp += T;
        if (B->Mp > B->maxMp)
            B->Mp = B->maxMp;
        if (B->Mp >= B->costMp)
        {
            B->Mp -= B->costMp;
            Dam = 2 * B->level * max(B->attack - A->defense, 0) / 100;
            A->Hp -= Dam;

            if (A->Hp <= 0)
            {
                A->Hp = 0;
                printf("%s used Headbutt!\n", B->name);
                printf("%s now has %d HP.\n", A->name, A->Hp);
                printf("%s is the winner! %s died in vain...\n", B->name, A->name);
                puts("");
                return;
            }
            printf("%s used Headbutt!\n%s now has %d HP.\n", B->name, A->name, A->Hp);
        }
        else
        {
            B->Mp += T;
            printf("%s used Rest!\n%s now has %d MP.\n", B->name, B->name, B->Mp);
        }
    }
}

int max(int a, int b)
{
    return a > b ? a : b;
}