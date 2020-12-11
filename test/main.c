#include <stdio.h>
#include <errno.h>
#include <string.h>
#define RED	"\033[31m"

int	main(int argc, char **argv, char **envp)
{
	int i;


	i = 0;
	while (i < 500)
	{
		printf("%d, %s\n", i, strerror(i));
		i++;
	}

}
