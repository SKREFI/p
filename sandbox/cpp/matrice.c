#include <stdio.h>
#include <stdlib.h>

#define INF 1001001001
#define getI(a) scanf("%d", &a)
#define getII(a, b) scanf("%d%d", &a, &b)
#define getIII(a, b, c) scanf("%d%d%d", &a, &b, &c)

#define max(a, b) (a < b ? b : a)
#define endl printf("\n");

#define F(i, L, R) for (int i = L; i < R; i++)  //next four are for "for loops"
#define FE(i, L, R) for (int i = L; i <= R; i++)
#define FF(i, L, R) for (int i = L; i > R; i--)
#define FFE(i, L, R) for (int i = L; i >= R; i--)

int** getMatrix(int n) {
    int **m = (int **)malloc(n * sizeof(int *));
    F(i, 0, n) m[i] = (int *)malloc(n * sizeof(int));
    return m;
}

int main() {
    int n;
    getI(n);
    int** m = getMatrix(n);
    
    F(i, 0, n) F(j, 0, n) m[i][j] = i + j;

    // F(i, 0, n) {
    //     F(j, 0, n) printf("%d ", m[i][j]);
    //     printf("\n");
    // }

    if (n % 2 == 1) printf("N odd so middle of matrix is: %d\n", m[n/2+1][n/2+1]);

    printf("Diagonala principala: ");
    F(i, 0, n) printf("%d ", m[i][i]);
    endl;
    printf("Diagonala secundara: ");
    F(i, 0, n) F(j, 0, n) if(i+j == n - 1) printf("%d ", m[i][j]);

        endl;

    // Done
    F(i, 0, n) free(m[i]);
    free(m);
    return 0;
}
