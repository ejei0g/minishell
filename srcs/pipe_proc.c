#include "minishell.h"
#include <sys/wait.h>

#define READ 0
#define WRITE 1

static int	printf_err()
{
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	return (-1);
}

int	pipe_process(t_stock_str *ms, t_env_list **head, char *line, int pipefd1[2], int pipefd2[2])
{
	int	status;
	pid_t	pid;

	if ((pid = fork()) < 0)
		return (printf_err());
	if (pid > 0)
	{
		waitpid(0, &status, 0);
		str_init(ms);
		parsing(line, ms, *head);
		if (ms->p_flag)
			pipe_process(ms, head, line, pipefd2, pipefd1);
		else
		{
			printf("hello\n");
			close(pipefd2[0]);//2
			close(pipefd2[1]);//2
			close(pipefd1[1]);//1
			dup2(pipefd1[0], STDIN_FILENO);
			close(pipefd1[0]);//1
			ms_proc(ms, head);

			return (0);
		}
	}
	else
	{//children
		close(pipefd2[1]);//2
		dup2(pipefd2[0], STDIN_FILENO);
		close(pipefd2[0]);//2

		close(pipefd1[0]);//1
		dup2(pipefd1[1], STDOUT_FILENO);
		close(pipefd1[1]);//1
		ms_proc(ms, head);
	}
	return (0);
}
		//원상복귀
		//dup2(ms->fd_inorg, STDIN_FILENO);
		//dup2(ms->fd_outorg, STDOUT_FILENO);
		/*
int	pipe_process(t_stock_str *ms, t_env_list **head, char *line)
{
	int	status;
	int	fdA[2];
	int	fdB[2];
	pid_t	pid;

	if (pipe(fdA) < 0)
		return (printf_err());
	if (pipe(fdB) < 0)
		return (printf_err());
	if ((pid = fork()) < 0)
		return (printf_err());
	if (pid > 0)
	{
		waitpid(0, &status, 0);

		close(fdA[WRITE]);
		str_init(ms);
		parsing(line, ms, *head);
		if (ms->p_flag)
		{
			printf("in second pipe\n");
			pipe_process(ms, head, line);
		}
		else
		{
			dup2(fdA[READ], STDIN_FILENO);
			ms_proc(*ms, head);
			return (1);
		}
		printf("stdin change test\n");
	//	args_free(ms);
	}
	else
	{//children
		close(fdA[READ]);
		dup2(fdA[WRITE], STDOUT_FILENO);
		ms_proc(*ms, head);
		//원상복귀
		//dup2(ms->fd_outorg, STDOUT_FILENO);
		printf("stdout change test\n");
		exit(0);
	}
	return (0);
}
		//원상복귀
		//dup2(ms->fd_inorg, STDIN_FILENO);
		//dup2(ms->fd_outorg, STDOUT_FILENO);
		*/
