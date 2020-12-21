#include "minishell.h"

void	free_envp_arr(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free((char *)envp[i]);
		i++;
	}
	free(envp);
}

void	ft_ms_exit(t_env_list **env)
{
	free_env_list(env);
	ft_putstr_fd("exit\n", 1);
	exit(1);
}
