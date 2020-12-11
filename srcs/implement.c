#include "minishell.h"
#define PWD_SIZE 10000

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
}

void	ft_ms_pwd(void)
{
	char pwd_box[PWD_SIZE];

	getcwd(pwd_box, PWD_SIZE);
	ft_putstr_fd(pwd_box, 1);
}

void	ft_ms_export(t_stock_str ms, t_env_list **env)
{
	int	i;
	t_env_list	*tmp;

	i = 1;
	//if ms->args 카운터가 1개일 때 나머지
	if (1)//ms.count == 1
		export_print(*env);//""추가해서 출력
	else
	{
		while (ms.args[i])
		{
			if ((tmp = find_env_key(env, ms.args[i])) != 0)
			{
				free(tmp->data);
				tmp->data = ft_strdup(ms.args[i]);
			}
			else
			{
				tmp = create_node(ms.args[i]);
				add_new_node(env, tmp);
			}
			i++;
		}
	}
	return ;
}

void	ft_ms_unset(t_stock_str ms, t_env_list **env)
{
	int	i;

	i = 1;
	while (ms.args[i])
	{
		delete_node(env, ms.args[i]);
		i++;
	}
	return ;
}

void	ft_ms_env(t_env_list *env)
{//=이 있는 경우만 출력, 
	printf_list(env);
	return ;
}
