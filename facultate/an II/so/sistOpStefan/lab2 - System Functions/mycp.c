#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define BUFFER_SIZE 4096

void	sm_putstr(char *s)
{
	while (*s)
	{
		write (1, s, 1);
		s++;
	}
}

int	copyfile(char *s, char *d)
{
	int	sid = open (s, O_RDONLY);
	int	did = open (d, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	char	buff[BUFFER_SIZE];

	if (sid == -1 || did == -1)
	{
		perror ("Error while opening files!\n");
		return (-1);
	}

	int	nread = read (sid, buff, BUFFER_SIZE);
	while (nread)
	{
		if (nread < 0)
		{
			perror ("Error while reading file!\n");
			return (-1);
		}
		write (did, buff, nread);
		nread = read (sid, buff, BUFFER_SIZE);
	}
	
	close (sid);
	close (did);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 3)
		return copyfile(argv[1], argv[2]);
	else
	{
		sm_putstr("Usage: ");
		sm_putstr(argv[0]);
		sm_putstr(" <first-file> <second-file>\n");
		return (-1);
	}
}
