  #include <sys/mman.h>
  #include <sys/stat.h>
  #include <sys/wait.h>
  #include <fcntl.h>
  #include <errno.h>
  #include <unistd.h>
  #include <stdio.h>
  #include <stdlib.h>

// gcc ex.c -lrt
// trebuie linking aparent?

int	main(int argc, char* argv[])
{
	pid_t 	dpid;
	size_t 	pageSize = getpagesize();
	char 	shm_name[] = "my_sh_mem";
	int	shm_fd;

	shm_fd = shm_open (shm_name, O_CREAT|O_RDWR, S_IRUSR|S_IWUSR);
	if (shm_fd < 0)
	{
		perror ("Eroarea la crearea memoriei partajate");
		return errno;
	}

	size_t shm_size = pageSize * argc;
	if (ftruncate (shm_fd, shm_size) == -1)
	{
		perror ("Eroare la alocarea memoriei partajate");
		shm_unlink (shm_name);
		return errno;
	}

	int offset = 0;
	for (int i = 1; i <= argc; i++)
	{
		char* shm_ptr = mmap (0, pageSize, PROT_READ|PROT_WRITE, MAP_SHARED, shm_fd, offset);

		if (shm_ptr == MAP_FAILED)
		{
			perror ("Eroare la distribuirea memoriei pentru proces");
			shm_unlink (shm_name);
			return errno;
		}

		dpid = fork();
		if (dpid < 0)
		{
			perror ("Eroare la crearea procesului");
			return errno;
		}
		else if (dpid == 0)
		{
			int offset = 0;
			int x = atoi (argv[i]);

			offset += sprintf (&shm_ptr[offset], "%d: %d ", x, x);
			
			if (x > 0)
			{
				while (x != 1)
				{
					offset += sprintf (&shm_ptr[offset], "%d ", x);
					if (x % 2 == 0)
						x = x / 2;
					else
						x = 3 * x + 1;
				}

				offset += sprintf(&shm_ptr[offset], "1\n");
				munmap (shm_ptr, pageSize);
				break;
			}
		}
		offset += pageSize;
	}

	while (wait (NULL) != -1)
		;

	if (dpid != 0)
	{
		char* shm_ptr = mmap (0, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);

		for (size_t i = 0; i < shm_size; i += pageSize)
			printf ("%s", &shm_ptr[i]);
		
		munmap (shm_ptr, shm_size);
	}

	printf ("Done Parent %d Me %d\n", getppid(), getpid());
	return 0;
}
