#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // declaring the file descriptor
    int fd1;

    // buffer where we hold the data
    char buf[128];
    
    // opening the files
    fd1 = open(argv[1], O_WRONLY | O_CREAT);
    
    // in case something goes wrong, for example the file path is not specfied when calling the procces
    if (fd1 == -1) { perror("File cannot be opened"); return EXIT_FAILURE; }

    // geting the data from the user
    scanf("%127s", buf);

    // writing it to fd1
    write(fd1, buf, strlen(buf));
    
    // closing the file descriptor
    close(fd1);

    return 0;
}