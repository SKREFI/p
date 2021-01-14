#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// Execute me
// cd "folder/path";if ($?) { gcc ex2-mycp.c -o ex2-mycp } ; if ($?) { .\ex2-mycp file1.txt file2.txt }
int main(int argc, char *argv[]) {
    // Some debuging data
    printf("Number of args: %d\n", argc);
    printf("Opend file \"%s\" to read to and \"%s\" to write.\n", argv[1], argv[2]);

    // File descriptor
    int in_file_des;  // should be used to read form file1
    int out_file_des;  // file descriptor 2, write to file2
    // "initializing" the descriptor
    //         file path, FLAGs
    in_file_des = open(argv[1], O_RDONLY | O_CREAT);
    out_file_des = open(argv[2], O_WRONLY | O_CREAT);
    // In case something wrong happens for example, file path is not spacified
    if (in_file_des == -1) { perror("Input file can't be opend."); return errno; }
    if (out_file_des == -1) { perror("Output file can't be opend."); return errno; }

    // buffer where we hold the data
    char buf[128];
    size_t nbytes;
    ssize_t bytes_read;
    nbytes = sizeof(buf);

    // getting the data from the in_file_des
    bytes_read = read(in_file_des, buf, nbytes);
    if (bytes_read < 0) { perror("Read error."); return errno; } else printf("Bytes read from the file: %d\n", bytes_read);
    printf("I have got this from the input file: %s\n", buf);

    char * token = strtok(buf, " ");
    pid_t pid = fork();

    if (pid < 0) { perror("Something wrong with the child."); return errno; }
    else if (pid == 0) {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    } else {
        printf("Parrent: %d; Child: %d;\n", getppid(), getpid());
        wait(NULL);
        printf("Child %d finished!.\n", getpid());
    }    
    
    // writing the data
    //    file, data, how many bytes
    write(out_file_des, buf, strlen(buf));
    // closing the file
    close(in_file_des);
    close(out_file_des);
    return 0;
}