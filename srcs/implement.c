/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   implement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:27:38 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/22 23:50:01 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ms_pwd(t_stock_str *ms)
{
	char	pwd_box[PWD_SIZE];

	getcwd(pwd_box, PWD_SIZE);
	ft_putstr_fd(pwd_box, 1);
	ms->err = 0;
	write(1, "\n", 1);
}

void	ft_ms_export(t_stock_str *ms, t_env_list **env)
{
	if (ms->args_cnt == 0)
		export_print(*env);
	else
	{
		if (ms->args[1][0] == '=')
			err_invalid(ms, 1);
		export_add(ms, env);
	}
	ms->err = 0;
	return ;
}

void	ft_ms_unset(t_stock_str *ms, t_env_list **env)
{
	int	i;

	i = 1;
	while (ms->args[i])
	{
		if (ft_strncmp(ms->args[i], "_", ft_strlen(ms->args[i])) == 0)
			;
		else if (ft_strchr(ms->args[i], '='))
			err_invalid(ms, i);
		else if (invalid_id(ms->args[i]) != 0)
			err_invalid(ms, i);
		else
			delete_node(env, ms->args[i]);
		i++;
	}
	ms->err = 0;
	return ;
}

void	ft_ms_env(t_stock_str *ms, t_env_list *env)
{
	t_env_list	*curr;

	curr = env;
	while (curr->next)
	{
		curr = curr->next;
		if (ft_strchr(curr->data, '='))
		{
			ft_putstr_fd(curr->data, 1);
			ms->err = 0;
			write(1, "\n", 1);
		}
	}
	return ;
}
