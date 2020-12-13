#include <unistd.h>
#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include <fcntl.h>

#include <sys/types.h>
#include <sys/wait.h>

#define MAX_BUF 1024
#define READ 0
#define WRITE 1

int	main(void)
{
	char *ls[3] = {"ls", "-al", 0};
	char *grep[3] = { "grep", "test", 0};

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
	/**
	 *  0 : STDIN_FILENO
	 *  1 : STDOUT_FILENO
	 *  2 : STDERR_FILENO
	 */

	/**
	 * fd[0] = read; //3
	 * fd[1] = write;//4
	 */
	int	dup_ret;
	int	fd_stdout;
	int	fd_stdin;

	fd_stdout = dup(STDOUT_FILENO);
	fd_stdin = dup(STDIN_FILENO);

	/**
	 * if pipe 1
	 *
	 * gnl
	 * 	line 111
	 * 	{
	 * 		parsing
	 * 		if (pipe on)
	 * 		{
	 * 			go process2
	 * 		}
	 * 		process
	 * 		free
	 * 	}
	 */

	int status;
	if (pid > 0)
	{
		//parsing
		//if (pipe on)
		//{
		// 	go	process2
		//}
		//process
		//o
		wait(&status);
		dup_ret = dup2(fd[0], STDIN_FILENO);
		execve("/bin/grep", grep, 0);
		//원상복귀
		dup_ret = dup2(fd_stdin, STDIN_FILENO);
	}
	else//children
	{
		dup_ret = dup2(fd[1], STDOUT_FILENO);
		execve("/bin/ls", ls, 0);
		//원상복귀
		//dup_ret = dup2(fd_stdout, STDOUT_FILENO);
	}
	exit(0);
}
