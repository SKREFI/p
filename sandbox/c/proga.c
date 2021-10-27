//progA
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    int i;
    char *arg[] = {"./progB", argv[2], argv[1], NULL};

    for (i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
    }
    execve("./progB", arg, NULL);
    return 0;
}