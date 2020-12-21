/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:27:19 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/21 21:27:21 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp_arr(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free((char *)envp[i]);
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
