#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_RESOURCES 	5
#define THREAD_NBR	5

int			available_resources = MAX_RESOURCES;
pthread_mutex_t		mtx;

int	decrease_count (int count)
{
	if (available_resources < count)
		return -1;
	else
	{
		pthread_mutex_lock(&mtx);
		available_resources -= count;
		printf ("Got %d resources %d remaining\n", count, available_resources);
		pthread_mutex_unlock(&mtx);
	}
	return 0;
}

int	increase_count (int count)
{
	pthread_mutex_lock(&mtx);
	available_resources += count;
	printf ("Released %d resources %d remaining\n", count, available_resources);
	pthread_mutex_unlock(&mtx);
	return 0;
}

void	*use_resources(void* v)
{
	int* resources_count = (int*)v;
	decrease_count(*resources_count);	
	increase_count(*resources_count);
	return NULL;
}

// gcc ex1.c -o t -pthread
int	main()
{
	pthread_t 	thr[THREAD_NBR];
	int		used_r[THREAD_NBR] = {2, 2, 1, 3, 2}; 
	pthread_mutex_init (&mtx, NULL);
	
	printf ("MAX_RESOURCES = %d\n", MAX_RESOURCES);

	for (int i = 0; i < THREAD_NBR; i++)
	{
		if (pthread_create(&thr[i], NULL, use_resources, &used_r[i]))
		{
			perror ("Eroare la crearea thread-ului.\n");
			return errno;
		}
	}

	for (int i = 0; i < 5; i++)
		if (pthread_join(thr[i], NULL))
		{
			perror ("Eroare la join-ul thread-urilor.\n");
			return errno;
		}

	pthread_mutex_destroy(&mtx);
}
