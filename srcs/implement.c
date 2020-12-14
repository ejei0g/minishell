#include "minishell.h"

void	ft_ms_cd(t_stock_str ms)
{
	char *path;

	//if ms->args 카운터가 2이상일 경우 에러처리.
	path = ms.args[1];

	//인수가 많거나 잘못된 경로일 경우 에러처리가 어떻게 되는지
	//자동인지 직접 설정해줘야 하는지
	if (path[0] == '/')
		path++;
	printf("path = %s\n", path);
	if (chdir(path) == -1)
		printf("erro\n");//errno
	write(1, "\n", 1);
}

void	ft_ms_pwd(void)
{
	char pwd_box[PWD_SIZE];

	getcwd(pwd_box, PWD_SIZE);
	ft_putstr_fd(pwd_box, 1);
	write(1, "\n", 1);
}

void	ft_ms_export(t_stock_str ms, t_env_list **env)
{
	if (ms.args_cnt == 0)
		export_print(*env);
	else
	{
		if (ms.args[1][0] == '=')
			err_invalid(ms, 1);
		export_add(ms, env);
		write(1, "\n", 1);//TODO:정상작동하는지 체크
	}
	return ;
}

void	ft_ms_unset(t_stock_str ms, t_env_list **env)
{
	int	i;

	i = 1;
	while (ms.args[i])
	{
		//if (ms.args[i][0] == '_' && ms.args[i][1] == '\0')
		if (ft_strncmp(ms.args[i], "_", ft_strlen(ms.args[i])) == 0)
			;
		else if (ft_strchr(ms.args[i], '='))
		{
			err_invalid(ms, i);
			/*
			ft_putstr_fd("bash: unset: '", 1);
			ft_putstr_fd(ms.args[i], 1);
			ft_putstr_fd("': not a valid identifier", 1);
			*/
		}
		else
			delete_node(env, ms.args[i]);
		i++;
	}
	write(1, "\n", 1);
	return ;
}

void	ft_ms_env(t_env_list *env)
{
	t_env_list *curr;

	curr = env;
	while (curr->next)
	{
		curr = curr->next;
		if (ft_strchr(curr->data, '='))
		{
			ft_putstr_fd(curr->data, 1);
			write(1, "\n", 1);
		}
	}
	return ;
}
