#include "minishell.h"

void	ft_ms_cd(t_stock_str ms)
{
	char *path;

	if (ms.args_cnt > 1)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 1);
		return ;
	}
	//apsolute path
	path = ms.args[1];
	if (chdir(path) == 0)
		return ;

	/*
	char pwds[1000];
	char *pwd;

	getcwd(pwds, 1000);
	pwd = ft_strdup(pwds);
	path = ft_strjoin(pwd, ms.args[1]);
	free(pwd);
	printf("path = %s\n", path);
	if (chdir(path) == 0)
	{
		free(path);
		return ;
	}
	*/



//	if (path[0] == '/')
//		path++;
//	printf("path = %s\n", path);
/*
	if (chdir(path) == -1)
		printf("errno\n");//errno:
	write(1, "\n", 1);
	*/
}

