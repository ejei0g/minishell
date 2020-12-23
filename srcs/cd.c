/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwyu <hwyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:53:57 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/23 23:25:19 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(t_stock_str *ms, char *path)
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

void	cd_pwd_proc(t_env_list **env, t_stock_str *ms)
{
	char		pwd_box[PWD_SIZE];
	t_env_list	*key;
	char		*old_pwd;
	char		*tmp;

	getcwd(pwd_box, PWD_SIZE);
	key = find_env_key(env, "PWD");
	old_pwd = key->data;
	key->data = ft_strjoin("PWD=", pwd_box);
	key = find_env_key(env, "OLDPWD");
	tmp = key->data;
	key->data = ft_strjoin("OLD", old_pwd);
	free(old_pwd);
	free(tmp);
	ms->err = 0;
}

char	*find_home(t_env_list **env, t_stock_str *ms)
{
	t_env_list	*home;
	char		*path;

	home = find_env_key(env, "HOME");
	if (ms->args_cnt == 0)
		path = ft_strdup(home->data + 5);
	else
		path = ft_strjoin(home->data + 5, ms->args[1] + 1);
	return (path);
}

void	ft_ms_cd(t_stock_str *ms, t_env_list **env)
{
	char	*path;

	if (ms->args_cnt > 1)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 1);
		ms->err = 1;
		return ;
	}
	if (ms->args_cnt == 0 || ms->args[1][0] == '~')
		path = find_home(env, ms);
	else
		path = ft_strdup(ms->args[1]);
	if (chdir(path) == 0)
	{
		cd_pwd_proc(env, ms);
		free(path);
		return ;
	}
	else
		cd_error(ms, path);
}
