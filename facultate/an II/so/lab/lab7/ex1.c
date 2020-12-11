#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_RESOURCES 5
#define THREADS	5

int available_resources = MAX_RESOURCES;
pthread_mutex_t mtx;

int increase_count(int count) {
    // printf("%d\n", count);
    pthread_mutex_lock(&mtx);
    available_resources += count;
    printf("Released %d resources %d remaining\n", count, available_resources);
    pthread_mutex_unlock(&mtx);
    return 0;
}

int	decrease_count(int count)
{
    // printf("%d\n", count);
	if (available_resources < count) return -1;
	else {
		pthread_mutex_lock(&mtx);
		available_resources -= count;
		printf ("Got %d resources %d remaining\n", count, available_resources);
		pthread_mutex_unlock(&mtx);
	}
	return 0;
}

void *use_resources(void* v) {
	int* resources_count = (int*)v;
	decrease_count(*resources_count);	
	increase_count(*resources_count);
	return NULL;
}

// -pthread flag must be used when calling me
// EXECUTE ME: 
// gcc ex1.c -o ex1 -pthread
int	main(int argc, char *argv[]) {
    pthread_t thr[THREADS];
    int used_r[THREADS] = {2, 2, 1, 3, 2};  
    pthread_mutex_init(&mtx, NULL);	

    printf("MAX_RESOURCES: %d\n", MAX_RESOURCES);
    printf("Threads: %d\n", THREADS);

    for (int i = 0; i < THREADS; i++)
        if (pthread_create(&thr[i], NULL, use_resources, &used_r[i])) { perror("Failed to create the thread.\n"); return errno; }

	for (int i = 0; i < 5; i++) 
		if (pthread_join(thr[i], NULL)){ perror ("Join error.\n"); return errno; }

	pthread_mutex_destroy(&mtx);
}