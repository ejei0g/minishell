#include "minishell.h"

#define READ 0
#define WRITE 1

extern void print_path(t_env_list **env);
extern int pipe_process(t_stock_str *ms, t_env_list **head, char *line, int p1[2], int p2[2]);


int fork_func(int pipefd1[2], int pipefd2[2], t_stock_str *ms, t_env_list **head)
{
    pid_t pid = fork();

    if (pid > 0)
    {
		sleep(1);
    }
    else
    {
        close(pipefd2[1]);//2
        dup2(pipefd2[0], STDIN_FILENO);
        close(pipefd2[0]);//2

        close(pipefd1[0]);//1
        dup2(pipefd1[1], STDOUT_FILENO);
        close(pipefd1[1]);//1

		ms_proc(*ms, head);
		exit(1);
    }
    return (pipefd1[0]);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int	i;
	//int	j;
	t_env_list	*head;
	t_stock_str ms;

	i = 0;
	ms.argv = argv;
	ms.argc = argc;
	ms.fd_inorg = dup(STDIN_FILENO);
	ms.fd_outorg = dup(STDOUT_FILENO);
	printf("argc = %d\n", argc);
	head = init_copy_envp(envp);
	ms.last_args = '\0';

	print_path(&head);
	//-------------
	int	pipefd1[2];
	int	pipefd2[2];
	int	tmp;


	pipe(pipefd1);
	pipe(pipefd2);
	tmp = pipefd1[0];
	printf("init tmp : %d pipefd1[0]: %d\n", tmp, pipefd1[0]);

	//-------------

	ft_putstr_fd(MINISHELL, 1);
	while ((i = get_next_line(0, &line)) > 0)
	{
		ms.l_idx = 0;
		while (line[ms.l_idx] != '\0')
		{
			str_init(&ms);
			if (i == 0)
			{
				exit(0);
				free(line);
			}
			parsing(line, &ms, head);
			//
			if (ms.p_flag == 1)
			{
				fork_func(pipefd2, pipefd1, &ms, &head);
				args_free(&ms);
				str_init(&ms);
				parsing(line, &ms, head);
				fork_func(pipefd1, pipefd2, &ms, &head);
			}
			args_free(&ms);
			str_init(&ms);
			parsing(line, &ms, head);
			close(pipefd2[0]);//1
			close(pipefd2[1]);//1
			close(pipefd1[1]);//2
			dup2(pipefd1[0], STDIN_FILENO);
			close(pipefd1[0]);//2
			ms_proc(ms, &head);


			args_free(&ms);
		}
		dup2(ms.fd_inorg, STDIN_FILENO);
		dup2(ms.fd_outorg, STDOUT_FILENO);
		ft_putstr_fd(MINISHELL, 1);
		free(line);
	}
	free(line);
	return (0);
}
