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
    fclose(fopen(argv[2], "w"));
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

    char* token = strtok(buf, " ");

    char words[128][64];

    int no_words = 0;
    while (token != NULL) {
        strcpy(words[no_words++], token);
        token = strtok(NULL, " ");
    }

    for (int i = 0; i < no_words; i++) {
        write(out_file_des, words[i], strlen(words[i]));
        write(out_file_des, " ", 1);
    }
    // closing the file
    close(in_file_des);
    close(out_file_des);
    return 0;
}