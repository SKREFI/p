#include <unistd.h>

void	sm_putstr(char s[])
{
	while (*s)
	{
		write (1, s, 1);
		s++;
	}
}

int	main()
{
	sm_putstr("Hello world!\n");
	return (0);
}
