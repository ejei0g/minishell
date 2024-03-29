/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwyu <hwyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:04:45 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/26 14:06:54 by hwyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_n_apace(t_stock_str *ms, char *line, t_env_list *head)
{
	if (line[ms->l_idx] == '\\')
		ms->args[ms->h][ms->w++] = line[++ms->l_idx];
	else if (p_sc_flag_parsing(ms, line) == 0)
		return (-1);
	else if (line[ms->l_idx] == '$')
		dollor_parsing(ms, line, head);
	else
		ms->args[ms->h][ms->w++] = line[ms->l_idx];
	return (0);
}

void	parsing_is_space(t_stock_str *ms, char *line)
{
	ms->args[ms->h][ms->w] = '\0';
	while (line[ms->l_idx + 1] == ' ')
		ms->l_idx++;
	while (null_flag(ms, line, 0) == 0)
		;
	while (line[ms->l_idx + 1] == ' ')
		ms->l_idx++;
	if (line[ms->l_idx + 1] == '|' || line[ms->l_idx + 1] == '<' ||
		line[ms->l_idx + 1] == ';' || line[ms->l_idx + 1] == '>')
		;
	else if (line[ms->l_idx + 1] != '\0')
	{
		ms->w = 0;
		ms->h++;
	}
}

void	line_parsing(char *line, t_stock_str *ms, t_env_list *head)
{
	while (line[ms->l_idx])
	{
		if (ms->sq_flag == 1)
			sq_flag_parsing(ms, line);
		else if (ms->dq_flag == 1)
			dq_flag_parsing(ms, line, head);
		else if (flag_check(ms, line[ms->l_idx]) == 0)
			;
		else if (line[ms->l_idx] == '>' || line[ms->l_idx] == '<')
		{
			if (redirect_parsing(ms, line) == -1)
				break ;
		}
		else if (line[ms->l_idx] != ' ')
		{
			if (parsing_n_apace(ms, line, head) == -1)
				break ;
		}
		else if (line[ms->l_idx] == ' ')
			parsing_is_space(ms, line);
		ms->l_idx++;
	}
}

int		parsing(char *line, t_stock_str *ms, t_env_list *head)
{
	int i;

	i = 0;
	ms->args = (char **)malloc(sizeof(char *) * (100));
	while (i < 100)
		ms->args[i++] = (char *)malloc(sizeof(char) * 1000);
	i = 0;
	ms->file_name = (char *)malloc(sizeof(char) * 100);
	while (i < 100)
		ms->file_name[i++] = '\0';
	line_parsing(line, ms, head);
	ms->args_cnt = ms->h;
	ms->args[ms->h][ms->w] = '\0';
	ms->last_args = ft_strdup(ms->args[ms->h]);
	free(ms->args[ms->h + 1]);
	ms->args[ms->h + 1] = NULL;
	g_err_num = 0;
	return (0);
}
