/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:28:33 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/23 00:11:33 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// !@?$%^*-+={}[] ., /
// ~
// #&
// ()<>

int	chk_invalid(char *s1, char *s2, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (ft_strchr(s2, s1[i]))
			return (1);
		i++;
	}
	return (0);
}

int	invalid_id(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
		{
			i++;
			break;
		}
		i++;
	}
	if (chk_invalid(s, INVALID, i))
		return (i);
	return (0);
}

void	err_invalid(t_stock_str *ms, int i)
{
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(ms->args[0], 1);
	ft_putstr_fd(": '", 1);
	ft_putstr_fd(ms->args[i], 1);
	ft_putstr_fd("': not a valid identifier", 1);
	write(1, "\n", 1);
	ms->err = 1;
}

char	*err_path_dir(void)
{
	ft_putstr_fd(strerror(errno), 1);
	return (NULL);
}
