#include "minishell.h"

void	pipe_func(t_stock_str *ms, t_env_list **head)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ms_proc(ms, head);
		exit(0);
	}
	else
	{
		waitpid(-1, &status, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}
