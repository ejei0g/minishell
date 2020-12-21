#include "minishell.h"

char	*find_home(t_env_list **env)
{
	t_env_list *home;
	char	*home_path;

	home = find_env_key(env, "HOME");
	home_path = ft_strdup(home->data + 5);
	printf("homeeee : %s\n", home_path);
	return(home_path);
}

void	ft_ms_cd(t_stock_str *ms, t_env_list **env)
{
	char	*path;
	char	*home;

	if (ms->args_cnt > 1)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 1);
		ms->err = 1;
		return ;
	}
	if (ms->args[1][0] == '~')
	{
		home = find_home(env);
		path = ft_strjoin(home, ms->args[1] + 1);
		free(home);
	}
	else
		path = ft_strdup(ms->args[1]);
	if (chdir(path) == 0)
	{
		free(path);
		return ;
	}
	else
	{
		ft_putstr_fd("bash: ", 1);
		ft_putstr_fd(ms->args[0], 1);
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(strerror(errno), 1);
		write(1, "\n", 1);
		ms->err = 1;
		free(path);
	}
}
