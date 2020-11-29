#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// Execute me
// cd "folder/path";if ($?) { gcc ex2-mycp.c -o ex2-mycp } ; if ($?) { .\ex2-mycp file1.txt file2.txt }
int main(int argc, char *argv[]) {
    // File descriptor
    int fd1;  // should be used to read form file1
    int fd2;  // file descriptor 2, write to file2

    printf("Number of args: %d\n", argc);

    // buffer where we hold the data
    char buf[128];

    // "initializing" the descriptor
    //         file path, FLAGs
    fd1 = open(argv[1], O_RDONLY | O_CREAT);
    fd2 = open(argv[2], O_WRONLY | O_CREAT);

    printf("Opend %s to read and %s to write.\n", argv[1], argv[2]);

    // In case something wrong happens for example, file path is not spacified
    if (fd1 == -1) {
        perror("Input file can't be opend.");
        return errno;
    }
    if (fd2 == -1) {
        perror("Output file can't be opend.");
        return errno;
    }

    size_t nbytes;
    ssize_t bytes_read;
    nbytes = sizeof(buf);

    // getting the data from the fd1
    bytes_read = read(fd1, buf, nbytes);
    if (bytes_read < 0) {
        perror("Read error.");
        return errno;
    } else
        printf("Bytes read from the file: %d\n", bytes_read);

    printf("I have got this from fd1: %s", buf);

    // writing the data
    //    file, data, how many bytes
    write(fd2, buf, strlen(buf));
    // I still don't get what are those weird chars from the end

    // closing the file
    close(fd1);
    close(fd2);
    return 0;
}