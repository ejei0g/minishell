#include "minishell.h"

//exit + free + 기타처리도 함께해주는 파일.
//

void	free_envp_arr(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
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
