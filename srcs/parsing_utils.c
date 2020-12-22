/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:04:26 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/22 17:16:18 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_init(t_stock_str *ms, int argc, char *argv[])
{
	ms->argv = argv;
	ms->argc = argc;
	ms->fd_inorg = dup(STDIN_FILENO);
	ms->fd_outorg = dup(STDOUT_FILENO);
	ms->last_args = NULL;
	ms->fd_flag = 0;
	ms->err = 0;
}

void	str_init(t_stock_str *ms)
{
	ms->w = 0;
	ms->h = 0;
	ms->p_flag = 0;
	ms->sc_flag = 0;
	ms->sq_flag = 0;
	ms->dq_flag = 0;
	ms->null_flag = 0;
}

void	args_free(t_stock_str *ms)
{
	int i;

	i = 0;
	free(ms->last_args);
	while (i < 100)
	{
		free(ms->args[i]);
		i++;
	}
	free(ms->args);
	free(ms->file_name);
}
