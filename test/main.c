#include <unistd.h>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#define MAX_BUF 1024
#define READ 0
#define WRITE 1

int	main(void)
{
	char buf[MAX_BUF];
	int  fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
	{
		printf("pipe error\n");
		return (-1);
	}
	if ((pid = fork()) < 0)
	{
		printf("fork error\n");
		return (-1);
	}
	/*
	printf("read : %d,write: %d\n", fd[0], fd[1]);
	printf("pid : %d\n", pid);
	write(fd[1], "hello world", 11);
	read(fd[0], buf, 5);
	printf("%s\n", buf);
	*/
	char *ls[3] = {"ls", "-al", 0};
	char *grep[3] = { "grep", "test", 0};
	if (pid > 0)
	{
		printf("pid : %d\n", pid);
		close(fd[READ]);
		strcpy(buf, "message from parent\n");
		write(fd[WRITE], buf, strlen(buf));

		printf("--------------------------\n");
		execve("/bin/ls", ls, 0);
		printf("--------------------------\n");

	}
	else
	{
		printf("pid : %d\n", pid);
		close(fd[WRITE]);
		read(fd[0], buf, MAX_BUF);
		printf("child got message : %s\n", buf);
		execve("/bin/grep", grep, 0);
	}
	exit(0);
}
