#include "minishell.h"
#include <sys/wait.h>

#define READ 0
#define WRITE 1

static int	printf_err()
{
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	return (-1);
}

int	pipe_process(t_stock_str *ms, t_env_list **head, char *line)
{
	printf("in pipe\n");
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) < 0)
		return (printf_err());
	if ((pid = fork()) < 0)
		return (printf_err());
	printf("forked%d,%d\n",fd[0], fd[1]);
	//printf("pid = %d", pid);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	if (pid > 0)
	{
	//	wait(&status);
		sleep(1);

		str_init(ms);
		parsing(line, ms, *head);
		printf("error\n");
		dup2(fd[READ], STDIN_FILENO);
		printf("after dup2\n");
		printf("p_flag = %d\n", ms->p_flag);
		if (ms->p_flag)
		{
			printf("in second pipe\n");
			pipe_process(ms, head, line);
		}
		else
		{
			printf("start msproc \n");
			printf("fd = %d\n", fd[0]);
			printf("args = %s\n", ms->args[0]);
			dup2(ms->fd_outorg, STDOUT_FILENO);
			execve("/bin/grep", ms->args, 0);
			//ms_proc(*ms, head);
			printf("after msproc \n");

		}
		//원상복귀
		dup2(ms->fd_inorg, STDIN_FILENO);
		printf("stdin change test\n");
		//free
	//	args_free(ms);
	}
	else
	{//children
		dup2(fd[WRITE], STDOUT_FILENO);
		ms_proc(*ms, head);
		//원상복귀
		//dup2(ms->fd_outorg, STDOUT_FILENO);
		printf("stdout change test\n");
	}
	return (0);
}
