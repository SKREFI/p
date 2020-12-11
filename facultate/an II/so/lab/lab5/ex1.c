#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

void collatz(int n) {
    while (n > 1) {
        printf("%d ", n);
        if (n % 2) n = n * 3 + 1;
        else n /= 2;
    }
    printf("\n");
}


// Compile this using lrt flag !!!
int	main(int argc, char *argv[])
{
    pid_t dp;
    size_t pageSize = getpagesize();
    char shm_name[] = "sh_mem";
    int shm_fd = shm_open(shm_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
    if (shm_fd < 0) { perror("Shared memory couldn't be created."); return errno; }

    size_t shm_size = (argc - 1) * pageSize;
    if (ftruncate(shm_fd, shm_size) == -1) { perror("Something went wrong with mmmory allocation."); return errno; }

    int offset = 0;
    for (int i = 0; i <= argc; i++) {
        char* shm_pointer = mmap(0, pageSize, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, offset);

        if (shm_pointer == MAP_FAILED) { perror("MAP FAILED"); return errno; }

        dp = fork();
        if (dp < 0) { perror("Failed to create process."); return errno; }
        else if (!dp) {
            int offset = 0;
            int n = atoi(argv[i]);

            if (n > 0) {
                while (n != 1) {
                    offset += sprintf(&shm_pointer[offset], "%d ", n);
                    if (n % 2) n = 3 * n + 1;
                    else n /= 2; 
                }
                break;
            }
        }
        offset += pageSize;
    }

    while(wait(NULL) != -1);

    if (dp) {
        char* shm_pointer = mmap(0, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);

        for (size_t i = 0; i < shm_size; i += pageSize) printf("%s", &shm_pointer[i]);
    }

    printf("Parrent: %d; Child %d is done.\n", getppid(), getpid());
}
