#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int	i;
	int	j;
	t_env_list	*head;
	t_stock_str ms;

	i = 0;
	head = init_copy_envp(envp);
	printf("argc : %d, argv[0] : %s\n", argc, argv[0]);
	ms.l_idx = 0;
	while ((i = get_next_line(0, &line)) > 0)
	{
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
			ms_proc(ms, &head);
			args_free(&ms);
		}
	}
	return (0);
}
