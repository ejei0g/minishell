/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:28:05 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/21 21:30:13 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_cmd(char *s1, char *s2)
{
	int	count;

	count = 0;
	if (ft_strlen(s1) > ft_strlen(s2))
		count = ft_strlen(s1);
	else
		count = ft_strlen(s2);
	if (ft_strncmp(s1, s2, count) == 0)
		return (1);
	return (0);
}

void	ms_proc(t_stock_str *ms, t_env_list **env)
{
	if (is_cmd(ms->args[0], ECHO))
		ft_ms_echo(ms);
	else if (is_cmd(ms->args[0], CD))
		ft_ms_cd(ms, env);
	else if (is_cmd(ms->args[0], PWD))
		ft_ms_pwd(ms);
	else if (is_cmd(ms->args[0], EXPORT))
		ft_ms_export(ms, env);
	else if (is_cmd(ms->args[0], UNSET))
		ft_ms_unset(ms, env);
	else if (is_cmd(ms->args[0], ENV))
		ft_ms_env(ms, *env);
	else if (is_cmd(ms->args[0], EXIT))
		ft_ms_exit(env);
	else
		ft_ms_else(ms, env);
	return ;
}
