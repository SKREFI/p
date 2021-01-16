#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char* encrypt(char* word, int key) {
    for (int i = 0; (i < 100 && word[i] != '\0'); i++)
        word[i] = word[i] + key;
    
    return word;
}

    // Must be compiled with the -lrt !!!
int main(int argc, char* argv[]) {
    // Some debuging data
    printf("Number of args: %d\n", argc);
    printf("Opend file \"%s\" to read to and \"%s\" to write.\n", argv[1], argv[2]);

    // fclose(fopen("out", "w"));

    // File descriptor
    int in_file_des;   // should be used to read form file1
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
    if (bytes_read < 0) { perror("Read error."); return errno; } else printf("Bytes read from the file: %ld\n", bytes_read);

    buf[bytes_read] = '\0';
    printf("I have got this from the input file: %s\n", buf);

    char* token = strtok(buf, " ");
    char words[128][64];

    int no_words = 0;
    while (token != NULL) {
        strcpy(words[no_words++], token);
        token = strtok(NULL, " ");
    }

    pid_t dpid;
    size_t pageSize = getpagesize();
    char shm_name[] = "my_sh_mem";
    int shm_fd;

    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (shm_fd < 0) { perror("Eroarea la crearea memoriei partajate"); return errno; }

	size_t shm_size = pageSize * no_words;
	if (ftruncate (shm_fd, shm_size) == -1) { perror ("Shared memory alocation error."); shm_unlink (shm_name); return errno; }

	int offset = 0;
	for (int i = 0; i < no_words; i++) {
		char* shm_ptr = mmap (0, pageSize, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, offset);

		if (shm_ptr == MAP_FAILED) { perror ("Memory distribution error."); shm_unlink (shm_name); return errno; }

		dpid = fork();
		if (dpid < 0) { perror ("Error creating the process."); return errno; }
		else if (dpid == 0) {
			int offset = 0;

            int key = atoi(argv[3]);

            int decrypt = 0; 
            if (argv[4]) decrypt = atoi(argv[4]);
            
            char* word;

            if (decrypt == 0) word = encrypt(words[i], key);
            else word = encrypt(words[i], -key);

            word[strlen(words[i])] = '\0';
            printf("Lungime: %d, Cuvant: %s\n", strlen(words[i]), word);

            offset += sprintf(&shm_ptr[offset], "%s", word);

            if (word) {
                offset += sprintf(&shm_ptr[offset], " ");
                munmap(shm_ptr, pageSize);
                break;
			}
		}
		offset += pageSize;
	}

	while(wait(NULL) != -1);

	if (dpid != 0){
		char* shm_ptr = mmap (0, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);

		for (size_t i = 0; i < shm_size; i += pageSize) {
            // printf ("%s", &shm_ptr[i]);

            write(out_file_des, &shm_ptr[i], strlen(&shm_ptr[i]));
            write(out_file_des, " ", 1);
        }
        
        write(out_file_des, '\0', 1);
        
        printf("\n");
		munmap (shm_ptr, shm_size);
	}

	printf ("Done Parent: %d; Child: %d\n", getppid(), getpid());
	return 0;
}
