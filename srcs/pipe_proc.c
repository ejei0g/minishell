/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:04:32 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/22 17:04:33 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_func(t_stock_str *ms, t_env_list **head)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ms_proc(ms, head);
		exit(0);
	}
	else
	{
		waitpid(-1, &status, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
	}
}
