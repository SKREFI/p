#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// forkls
int main(int argc, char *argv[]) {
    pid_t pid = fork();
    if (pid < 0) return errno;
    else if (pid == 0) {
        char *argv[] = {"ls", NULL};
        execve("/bin/ls", argv, NULL);
        perror(NULL);
    } else {
        printf("Parrent: %d;Child: %d;\n", getppid(), getpid());
        wait(NULL);
        printf("Child %d finished!.\n", getpid());
    }
    printf("\n");
}