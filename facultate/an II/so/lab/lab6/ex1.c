#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>

void* fun(void *v) {
    char* arg = (char*) v;

    const int n = strlen(arg);
    char reverse[n+1];
    
    for (int i = 0; i < n; i++) {
        // printf("%c", arg[n - i - 1]);
        reverse[i] = arg[n - i - 1];
    }
    reverse[n] = '\0';

    printf("%s\n", reverse);
}
// Call me with pthread flag!!
// gcc -pthread ex1.c -o ex1 && ./ex1 helloDude
int main(int argc, char *argv[]){
    // int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *args);
    if (argc == 1) { perror("Call me with a string argument."); return errno;}
    pthread_t thr;
    if (pthread_create(&thr, NULL, fun, argv[1])){ perror("Failed to create a thread."); return errno; }

    // int pthread_join(pthread_t threaad, void **value_pointer);
    char* result;
    if (pthread_join(thr, &result)) { perror(NULL); return errno; }
    printf("%s\n", result); // not working, I m not sure how this is working
}   