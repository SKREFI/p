#include <stdio.h>
#include <string.h>

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
#define MAX_SIZE 1000

int* count_occurrences(char* str, char* word) {
    int found_at, count = 0;

    int* found_at_at = (int*)malloc(strlen(str) * sizeof(int));
    F(i, 0, strlen(str))
    found_at_at[i] = -1;
    int k = 0;

    for (int i = 0; i <= strlen(str) - strlen(word); i++) {
        found_at = 1;

        if (i == 0 || str[i] == ' ') {
            if (i != 0) i++;
            for (int j = 0; j < strlen(word); j++) {
                if (str[i++] != word[j]) {
                    found_at = 0;
                    break;
                }
            }
            if (i != strlen(str))
                if (str[i] != ' ') found_at = 0;
            i--;
            if (found_at) found_at_at[k++] = i - strlen(word) + 1;
        }
    }
    return found_at_at;
}

int main() {
    char str[MAX_SIZE];
    char word[MAX_SIZE];

    printf("String: ");
    gets(str);
    printf("Word: ");
    gets(word);

    int* found_at = count_occurrences(str, word);
    // Eroare: Lista initiala contine indexi la care se gaseste cuvantul target.
    // Dupa ce se inlocuieste/elimina un cuvant, indexi urmatori se micsoreaza cu len(word)
    for (int i = 0; found_at[i] != -1; i++) {
        int k = found_at[i];

        while (found_at[k + strlen(word) + 1] != '\0') {
            str[k] = str[k + strlen(word)];
            k++;
            str[k] = '\0';
        }

    }

    printf("%s", str);

    free(found_at);
    return 0;
}