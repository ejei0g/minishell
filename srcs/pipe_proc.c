#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

//#include "minishell.h"

#define MAX_BUF 1024
#define READ 0
#define WRITE 1

//int pipe_process(t_stock_str ms, t_env_list **head);
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

int	main(void)
{
	char *ls[3] = {"ls", "-al", 0};
	char *grep[3] = { "grep", "list", 0};

	int	fd[2];
	pid_t	pid;
	int	fd_stdout;
	int	status;
	int	dup_ret;

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

	//fd_stdout = dup(STDOUT_FILENO);

	char buf[1000];
	if (pid > 0)
	{
		//parsing
		//if (pipe on)
		//{
		// 	go	process2
		//}
		//process
		wait(&status);
		dup_ret = dup2(fd[0], STDIN_FILENO);
		execve("/bin/grep", grep, 0);
		//원상복귀
		//dup_ret = dup2(fd_stdout, STDOUT_FILENO);
	}
	else//children
	{
		//write 를 ,stdoup
		dup_ret = dup2(fd[1], STDOUT_FILENO);
		execve("/bin/ls", ls, 0);
	}
	exit(0);
}
