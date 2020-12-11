#include "minishell.h"

/*
 * 	args;
 * 	envs;
 */

void	printf_ms(t_stock_str ms)
{
	int	i;

	i = 0;
	while (ms.args[i])
	{
		printf("%s\n", ms.args[i]);
		i++;
	}
	printf("finished ms\n");
	return ;
}

void	ft_ms_execve(t_stock_str ms, char *s, t_env_list *env)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		execve(s, ms.args, 0);
	}
	else
	{

	}
}

void	ms_proc(t_stock_str ms, t_env_list **env)
{
	printf_ms(ms);
	if (ft_strncmp(ms.args[0], "echo", 4) == 0)
		;//TODO: 함수추가
	else if (ft_strncmp(ms.args[0], "cd", 2) == 0)
		ft_ms_cd(ms);
	else if (ft_strncmp(ms.args[0], "pwd", 3) == 0)
		ft_ms_pwd();
	else if (ft_strncmp(ms.args[0], "export", 6) == 0)
		ft_ms_export(ms, env);
	else if (ft_strncmp(ms.args[0], "unset", 5) == 0)
		ft_ms_unset(ms, env);
	else if (ft_strncmp(ms.args[0], "env", 3) == 0)
		ft_ms_env(*env);
	else if (ft_strncmp(ms.args[0], "exit", 4) == 0)
		exit(1);//free + error + extra;
	else
		ft_ms_execve(ms, ms.args[0], *env);
//	printf("\n");
	return ;
}
