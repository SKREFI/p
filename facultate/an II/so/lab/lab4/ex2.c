#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// forkls
int main(int argc, char *argv[]) {
    pid_t pid = fork();
    if (argv[1] == NULL) {
        // why is this called 2 time, I don't get it
        printf("You must give an integer argument.\nFor example: %s 24\n", argv[0]);
        return -1;
    } else {
        // child, where we apply the formula
        int n = atoi(argv[1]);
        if (pid < 0) return errno;
        else if (pid == 0) {
            while(n > 1) {
                printf("%d ", n);
                if (n % 2 == 0) n /= 2;
                else n = 3 * n + 1;
            }
        } else {
            printf("Parrent: %d;Child: %d;\n", getppid(), getpid());
            wait(NULL);
            printf("Child %d finished!.\n", getpid());
        }
        printf("\n");
    }
}