#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
	pid_t pid = fork();
	if (pid < 0)
	{
		perror ("Problema la initializare proces fiu\n");
		return errno;
	}
	else if (pid == 0)
	{
		// CHILD	
		char *argv[] = {"ls", NULL};
		execve("/usr/bin/ls", argv, NULL);
		perror("Eroare la apelarea /usr/bin/ls");
	}
	else
	{
		// PARENT
		printf ("My PID = %d, Child PID = %d.\n", getppid(), getpid());
		wait (NULL);
		printf ("Child %d finished.\n", getpid());
	}
}
