/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:04:40 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/22 17:04:41 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sq_flag_parsing(t_stock_str *ms, char *line)
{
	while (line[ms->l_idx] != '\'')
		ms->args[ms->h][ms->w++] = line[ms->l_idx++];
	ms->sq_flag = 0;
}

void	dq_flag_parsing(t_stock_str *ms, char *line, t_env_list *head)
{
	while (line[ms->l_idx] != '\"')
	{
		if (line[ms->l_idx] == '\\')
		{
			ms->l_idx++;
			ms->args[ms->h][ms->w++] = line[ms->l_idx++];
		}
		else if (line[ms->l_idx] == '$')
		{
			dollor_parsing(ms, line, head);
			ms->l_idx++;
		}
		else
			ms->args[ms->h][ms->w++] = line[ms->l_idx++];
	}
	ms->dq_flag = 0;
}

int		null_flag(t_stock_str *ms, char *line, int i)
{
	if (ms->null_flag == -1)
		return (-1);
	if (ft_strncmp(ms->args[0], "echo", 4) != 0)
	{
		if (ms->null_flag == 0)
			ms->null_flag = -1;
		return (-1);
	}
	i = ms->l_idx;
	ms->l_idx++;
	if (line[ms->l_idx] == '-' && line[ms->l_idx + 1] == 'n')
	{
		ms->l_idx++;
		while (line[ms->l_idx] == 'n')
			ms->l_idx++;
		if (line[ms->l_idx] == ' ' || line[ms->l_idx] == '\0')
		{
			ms->null_flag = 1;
			return (0);
		}
	}
	ms->l_idx = i;
	if (ms->null_flag == 0)
		ms->null_flag = -1;
	return (-1);
}

int		p_sc_flag_parsing(t_stock_str *ms, char *line)
{
	if (line[ms->l_idx] == '|')
	{
		ms->p_flag = 1;
		ms->l_idx++;
		while (line[ms->l_idx] == ' ')
			ms->l_idx++;
		return (0);
	}
	else if (line[ms->l_idx] == ';')
	{
		ms->sc_flag = 1;
		ms->l_idx++;
		while (line[ms->l_idx] == ' ')
			ms->l_idx++;
		return (0);
	}
	return (-1);
}
