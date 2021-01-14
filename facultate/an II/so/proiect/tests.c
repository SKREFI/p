#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// forkls
int main(int argc, char *argv[]) {
    pid_t pid = fork();
    pid_t pid2 = fork();

    if (pid == 0) { printf("Parent\n"); } else { printf("Child\n"); }
}