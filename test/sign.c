#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/types.h>
#include <signal.h>

//gnl while 밑에
/*
if (i == 0)
{
	printf("exit\n");
	exit(0);
}
*/

//sigint == ctrl+c

/*
void	process_signal(int sign)
{
	if (sign == SIGKILL)
	{
		write(1, "sigkill\n", 8);
		write(1, "\nbash", 5);

	}
	else if (sign == SIGQUIT)
	{
		write(1, "sigquit\n", 8);
		write(1, "\nbash", 5);
	}

	int i;

	i = sign;
	write(1, "\nbash", 5);
}
*/

void	sig_handler(int signo)
{
	printf("i received SIGINT(%d)\n", SIGINT);
}

int	main(void)
{
	int i;
	i=0;

	signal(SIGINT, (void *)sig_handler);

	while (1)
	{
		printf("%d\n", i);
		sleep(1);
		i++;
	}
	return (0);
}
