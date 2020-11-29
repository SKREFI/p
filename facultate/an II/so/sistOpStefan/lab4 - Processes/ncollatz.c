#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	pid_t pid;

	printf ("Starting parent %d\n", getpid());

	for (int i = 1; i <= argc; i++)
	{
		pid = fork();
		if (pid < 0)
		{
			perror ("Problema la initializare proces fiu\n");
			return errno;
		}
		else if (pid == 0)
		{
			// CHILD
			int x = atoi(argv[i]);
			if (x > 0)
			{
				printf ("%d: ", x);
				while (x != 1)
				{
					printf ("%d ", x);
					if (x % 2 == 0)
						x = x / 2;
					else
						x = 3 * x + 1;
				}
				printf ("1\n");
				break;
			}
		}
	}

	while (wait(NULL) != -1)
		;
	
	printf ("Done Parent %d Me %d\n", getppid(), getpid());
	return 0;	
}
