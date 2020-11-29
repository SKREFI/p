#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int	main(int argc, char *argv[])
{
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("Problema la initializare proces fiu\n");
		return errno;
	}
	else if (pid == 0)
	{
		// CHILD
		if (argc != 2)
			printf ("Usage: %s <N>\n", argv[0]);
		else
		{
			int x = atoi(argv[1]);
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
			}
		}
	}
	else
	{
		// PARENT
		wait (NULL);
		printf ("Child %d finished.\n", getpid());
	}
	return 0;
}
