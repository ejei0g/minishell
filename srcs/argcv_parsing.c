/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argcv_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:03:53 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/22 17:03:54 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	argv_parsing(t_stock_str *ms, int i)
{
	int j;

	j = 0;
	if (ms->argv[i] == NULL)
		return ;
	while (ms->argv[i][j])
		ms->args[ms->h][ms->w++] = ms->argv[i][j++];
	ms->args[ms->h][ms->w] = '\0';
	return ;
}

int		all_argv_parsing(t_stock_str *ms, char *line)
{
	int i;

	i = 1;
	if (line[ms->l_idx] == '*' || line[ms->l_idx] == '@')
	{
		while (i < ms->argc)
		{
			argv_parsing(ms, i++);
			if (ms->argv[i] == NULL)
			{
				ms->l_idx++;
				return (0);
			}
			ms->args[ms->h++][ms->w] = '\0';
			ms->w = 0;
		}
		ms->l_idx++;
		return (0);
	}
	return (1);
}

void	env_parsing(t_stock_str *ms, t_env_list *head, char *a)
{
	int			i;
	t_env_list	*test;

	i = 0;
	test = find_env_key(&head, a);
	if (test != NULL)
	{
		while (test->data[i] != '=')
			i++;
		i++;
		while (test->data[i])
		{
			ms->args[ms->h][ms->w] = test->data[i];
			ms->w++;
			i++;
		}
	}
	ms->l_idx--;
}
