#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int			THREAD_NBR = 5;
int			S;
pthread_mutex_t		mtx;
sem_t			sem;

int	barrier_point()
{
	pthread_mutex_lock(&mtx);
	S--;

	if (S != 0)
	{
		pthread_mutex_unlock(&mtx);
		if (sem_wait(&sem))
		{
			perror ("Eroare la wait-ul semaforului\n");
			return errno;
		}
	}
	else
	{
		pthread_mutex_unlock(&mtx);
		for (int i = 0; i < THREAD_NBR - 1; i++)
		{
			if (sem_post(&sem))
			{
				perror ("Eroare la revenirea semaforului\n");
				return errno;
			}
		}
	}

	return 0;
}

void*	tfun(void *v)
{
	int *tid = (int *)v;

	printf ("%d reached the barrier\n", *tid);
	barrier_point();
	printf ("%d passed the barrier\n", *tid);

	return NULL;
}

// gcc ex2.c -o semafor -pthread
int	main(int argc, char ** argv)
{
	if (argc != 1)
		THREAD_NBR = atoi(argv[1]);

	pthread_t 	thr[THREAD_NBR];
	S = THREAD_NBR;

	if (pthread_mutex_init(&mtx, NULL))
	{
		perror ("Eroare la initializarea mutexului\n");
		return errno;
	}
	
	if (sem_init(&sem, 0, 0))
	{
		perror ("Eroare la initializarea semaforului\n");
		return errno;
	}

	printf ("NTHRS = %d\n", THREAD_NBR);

	for (int i = 0; i < THREAD_NBR; i++)
	{
		int* j = (int*)malloc(sizeof(int));
		*j = i;
		if (pthread_create(&thr[i], NULL, tfun, j))
		{
			perror ("Eroare la crearea thread-ului.\n");
			return errno;
		}
	}

	for (int i = 0; i < THREAD_NBR; i++)
		if (pthread_join(thr[i], NULL))
		{
			perror ("Eroare la join-ul thread-urilor.\n");
			return errno;
		}

	pthread_mutex_destroy(&mtx);
	sem_destroy(&sem);

	return (0);
}
