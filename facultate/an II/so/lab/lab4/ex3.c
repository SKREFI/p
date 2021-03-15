#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	pid_t pid;
	printf ("First parent %d\n", getpid());

    // for each argument
	for (int i = 1; i <= argc; i++) {
		pid = fork();
		if (pid < 0) return errno;
		else if (pid == 0) {
			int n = atoi(argv[i]);
			while (n > 1) {
					printf ("%d ", n);
					if (n % 2 == 0) n /= 2;
					else n = 3 * n + 1;
			}
            printf("\n");
		} else {
            wait(NULL);
        	printf ("Done Parent %d Child %d\n", getppid(), getpid());
        }
	}	
	return 0;	
}
