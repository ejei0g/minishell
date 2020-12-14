#include "minishell.h"

#define READ 0
#define WRITE 1

extern void print_path(t_env_list **env);
extern int pipe_process(t_stock_str *ms, t_env_list **head, char *line);

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int	i;
	int	j;
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
	int	pipe_a[2];
	int	pipe_b[2];

	pipe(pipe_a);
	pipe(pipe_b);

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

			printf("\n------------------------------------\n");
			j = 0;
			while (ms.args[j])
			{
				printf("ms.args[%d] = %s\n", j, ms.args[j]);
				j++;
			}
		       	printf("p_flag = %d\t", ms.p_flag);
			printf("sc_flag = %d\t", ms.sc_flag);
			printf("l_idx = %d\n", ms.l_idx);
			printf("sq_flag = %d\t", ms.sq_flag);
			printf("dq_flag = %d\t", ms.dq_flag);
			//printf("ms->l_idx = %c\n", line[ms.l_idx]);
			printf("ms->last_args = %s\n", ms.last_args);
			printf("ms->args_cnt = %d\t", ms.args_cnt);
			printf("ms->null_flag = %d\n", ms.null_flag);
			printf("------------------------------------\n");
		//원상복귀
		//dup2(ms->fd_inorg, STDIN_FILENO);
		//dup2(ms->fd_outorg, STDOUT_FILENO);

			if (ms.p_flag)
			{
				printf("in pflag\n");
				//close(pipe_a[1]);
				dup2(pipe_a[1], STDOUT_FILENO);
				ms_proc(ms, &head);
				dup2(ms.fd_outorg, STDOUT_FILENO);
				printf("out proc\n");
			}
			else
			{
				printf("%d %d\n", pipe_a[0], pipe_a[1]);
				dup2(pipe_a[0], STDIN_FILENO);
				ms_proc(ms, &head);
				dup2(ms.fd_inorg, STDIN_FILENO);
			}
//			write(1, "finish\n", 7);
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
