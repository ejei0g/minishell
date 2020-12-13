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
	int	fd[2];
	pid_t	pid;
//	int	status;

	//int	fd_stdout = dup(STDOUT_FILENO);
	//int	fd_stdin = dup(STDIN_FILENO);

	if (pipe(fd) < 0)
		return (printf_err());
	if ((pid = fork()) < 0)
		return (printf_err());
	/*
	if (pid == 0)
	{
		ms_proc(*ms, head);

	}
	else
	{
		//wait(&status);
		sleep(2);
		printf("%s\n", line);
	}
	*/
	if (pid > 0)
	{
	//	wait(&status);

		sleep(1);
		printf("hello\n");

		//if (line[ms->l_idx] == '\0')
		//	return (0);
		//printf("l_idx = %d\n", ms->l_idx);
		args_free(ms);
		str_init(ms);
		//printf("l_idx = %d\n", ms->l_idx);
		parsing(line, ms, *head);
		printf("cmd : %s\n", ms->args[0]);
		if (ms->p_flag)
		{
			pipe_process(ms, head, line);
		}
		dup2(fd[READ], STDIN_FILENO);
		ms_proc(*ms, head);
		//원상복귀
		//dup2(fd_stdin, STDIN_FILENO);
		//free
	}
	else
	{//children
		dup2(fd[WRITE], STDOUT_FILENO);
		ms_proc(*ms, head);
		//원상복귀
		//dup2(fd_stdout, STDOUT_FILENO);
		//free/?
	}
	return (0);
}
