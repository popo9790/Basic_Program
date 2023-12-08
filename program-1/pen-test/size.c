#include <stdio.h>
#include <stdlib.h>
#define N 2
#define M 3

int main(void)
{
    // Declaration
    int i, j, *tmp;
    int a[N * M];
    int b[N][M];
    int c[M][N];
    int *pa = malloc(sizeof(int) * M * N);
    int **pb = malloc(sizeof(int *) * N);
    int **pc = malloc(sizeof(int *) * M);
    // Allocate second level resources all at once to reduce allocation overhead.
    tmp = malloc(sizeof(int) * M * N);
    for (i = 0; i < N; i++)
        pb[i] = tmp + i * M;
    tmp = malloc(sizeof(int) * M * N);
    for (i = 0; i < M; i++)
        pc[i] = tmp + i * N;
    // Print
    printf("sizeof(int)       : %2zu\n", sizeof(int));
    printf("sizeof(int[M])    : %2zu\n", sizeof(int[M]));
    printf("sizeof(int[N])    : %2zu\n", sizeof(int[N]));
    printf("sizeof(int[N][M]) : %2zu\n", sizeof(int[N][M]));
    printf("sizeof(int[M][N]) : %2zu\n", sizeof(int[M][N]));
    printf("sizeof(void*)     : %2zu\n", sizeof(void *));
    printf("sizeof(int*)      : %2zu\n", sizeof(int *));
    printf("sizeof(int**)     : %2zu\n", sizeof(int **));
    printf("sizeof   a        : %2zu\n", sizeof a);
    printf("sizeof  *a        : %2zu\n", sizeof *a);
    printf("sizeof   b        : %2zu\n", sizeof b);
    printf("sizeof  *b        : %2zu\n", sizeof *b);
    printf("sizeof **b        : %2zu\n", sizeof **b);
    printf("sizeof   c        : %2zu\n", sizeof c);
    printf("sizeof  *c        : %2zu\n", sizeof *c);
    printf("sizeof **c        : %2zu\n", sizeof **c);
    printf("sizeof   pa       : %2zu\n", sizeof pa);
    printf("sizeof  *pa       : %2zu\n", sizeof *pa);
    printf("sizeof   pb       : %2zu\n", sizeof pb);
    printf("sizeof  *pb       : %2zu\n", sizeof *pb);
    printf("sizeof **pb       : %2zu\n", sizeof **pb);
    printf("sizeof   pc       : %2zu\n", sizeof pc);
    printf("sizeof  *pc       : %2zu\n", sizeof *pc);
    printf("sizeof **pc       : %2zu\n", sizeof **pc);
    // Free
    free(pa);
    free(pb[0]);
    free(pb);
    free(pc[0]);
    free(pc);
    return 0;
}