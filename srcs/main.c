#include "minishell.h"

extern void print_path(t_env_list **env);

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
	printf("argc = %d\n", argc);
	head = init_copy_envp(envp);
	ms.last_args = '\0';

	print_path(&head);

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
			printf("\n---------------------\n");
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
			printf("ms->l_idx = %c\n", line[ms.l_idx]);
			printf("ms->last_args = %s\t", ms.last_args);
			printf("ms->args_cnt = %d\n", ms.args_cnt);
			ms_proc(ms, &head);
			//write(1, "finish\n", 7);
			args_free(&ms);
		}
		ft_putstr_fd(MINISHELL, 1);
	}
	return (0);
}
