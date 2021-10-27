#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

char* replaceWord(const char* s, const char* target, const char* replacing) {
    int i, count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], target) == &s[i]) {
            count++;
            i += strlen(target) - 1;
        }
    }

    char* result = (char*)malloc(i + count * (strlen(replacing) - strlen(target)) + 1);

    i = 0;
    while (*s) {
        if (strstr(s, target) == s) {
            strcpy(&result[i], replacing);
            i += strlen(replacing);
            s += strlen(target);
        }
        else result[i++] = *s++;
    }

    result[i] = '\0';
    return result;
}

int main() {
    char str[MAX_SIZE];
    gets(str);
    char target[MAX_SIZE];
    gets(target);
    char replacing[MAX_SIZE];
    gets(replacing);


    char* result = replaceWord(str, target, replacing);
    printf("Rezultat: %s\n", result);

    free(result);
    return 0;
}
