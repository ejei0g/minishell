/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwyu <hwyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 17:53:57 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/21 19:52:51 by hwyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home(t_env_list **env)
{
	t_env_list	*home;
	char		*home_path;

	home = find_env_key(env, "HOME");
	home_path = ft_strdup(home->data + 5);
	return (home_path);
}

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
		ms->err = 0;
		free(path);
		return ;
	}
	else
		cd_error(ms, path);
}
