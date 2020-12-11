#include "minishell.h"

void	print_path(t_env_list **env)
{
	t_env_list *path;
	char	**paths;

	path = find_env_key(env, "PATH");
	printf("%s\n", path->data + 5);
	paths = ft_split(path->data + 5, ':');
	

	//dir 열고
	//정보 읽고
	// dir 닫고
	int i;
	i = 0;
	while (paths[i])
	{
		printf("%s\n", paths[i]);
		i++;
	}

	//paths free;
	free_envp_arr(paths);
}

void	ft_ms_execve(t_stock_str ms, char *s, t_env_list *env)
{
	int	pid;
	t_env_list	*tmp;

	tmp = env;
	pid = fork();
	printf("%s\n", tmp->data);
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
	if (ft_strncmp(ms.args[0], ECHO, 4) == 0)
		ft_ms_echo(ms);
	else if (ft_strncmp(ms.args[0], CD, 2) == 0)
		ft_ms_cd(ms);
	else if (ft_strncmp(ms.args[0], PWD, 3) == 0)
		ft_ms_pwd();
	else if (ft_strncmp(ms.args[0], EXPORT, 6) == 0)
		ft_ms_export(ms, env);
	else if (ft_strncmp(ms.args[0], UNSET, 5) == 0)
		ft_ms_unset(ms, env);
	else if (ft_strncmp(ms.args[0], ENV, 3) == 0)
		ft_ms_env(*env);
	else if (ft_strncmp(ms.args[0], EXIT, 4) == 0)
		ft_ms_exit(env);
	//else
	//	ft_ms_execve(ms, ms.args[0], *env);
	return ;
}
