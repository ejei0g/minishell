#include "minishell.h"

#define READ 0
#define WRITE 1

extern void print_path(t_env_list **env);
extern int pipe_process(t_stock_str *ms, t_env_list **head, char *line, int p1[2], int p2[2]);

void	sig_handler(void)
{
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(MINISHELL, 1);
}

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
		ms_proc(*ms, head);
		exit(0);
	}
	else
	{
		waitpid(-1, &status, 0);
		//status = WEXITSTATUS(status);
		//ms->err = status;
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
	//printf("a\n");
}
void	sig_quit(int nb)
{
	(void)nb;
	if (write(STDOUT_FILENO, " \b\b \b", 5) < 0)
		return ;
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int	i;
	//int	j;
	t_env_list	*head;
	t_stock_str ms;
	//int			status;

	i = 0;
	ms.argv = argv;
	ms.argc = argc;
	ms.fd_inorg = dup(STDIN_FILENO);
	ms.fd_outorg = dup(STDOUT_FILENO);
	head = init_copy_envp(envp);
	ms.last_args = '\0';
	ms.fd_flag = 0;
	ms.err = 0;

	print_path(&head);
	//--signal
	signal(SIGINT, (void *)sig_handler);
	signal(SIGQUIT, sig_quit);
	//-------------

	//-------------
	ft_putstr_fd(MINISHELL, 1);
	while ((i = get_next_line(0, &line)) > 0)
	{
		ms.l_idx = 0;
		while (line[ms.l_idx] != '\0')
		{
			str_init(&ms);
			parsing(line, &ms, head);
			if (ms.p_flag == 1)
			{
				pipe_func(&ms, &head);
				args_free(&ms);
				continue ;
			}
			if (ms.file_name[0] != '>' && ms.file_name[0] != '<')
				ms_proc(ms, &head);
			dup2(ms.fd_inorg, STDIN_FILENO);
			args_free(&ms);
		}
		dup2(ms.fd_inorg, STDIN_FILENO);
		dup2(ms.fd_outorg, STDOUT_FILENO);
		ft_putstr_fd(MINISHELL, 1);
		free(line);
	}
	if (i == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	free(line);
	return (0);
}
