/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwyu <hwyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 17:03:34 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/23 23:04:16 by hwyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	sig_quit(int i)
{
	char	*nbr;

	g_err_num = 131;
	nbr = ft_itoa(i);
	ft_memdel(nbr);
}

void	sig_handler(void)
{
	ft_putstr_fd("\b\b  \n", 1);
	ft_putstr_fd(MINISHELL, 1);
	g_err_num = 130;
}

void	ms_print(t_stock_str *ms, char *line, t_env_list **head)
{
	ms->l_idx = 0;
	if (line[0] == '|')
	{
		ft_putstr_fd("bash: syntax error near unexpected token '|'\n", 1);
		ms->err = 2;
		ft_putstr_fd(MINISHELL, 1);
		return ;
	}
	while (line[ms->l_idx] != '\0')
	{
		str_init(ms);
		parsing(line, ms, *head);
		if (ms->p_flag == 1)
		{
			pipe_func(ms, head);
			args_free(ms);
			continue ;
		}
		if (ms->file_name[0] != '>' && ms->file_name[0] != '<')
			ms_proc(ms, head);
		dup2(ms->fd_inorg, STDIN_FILENO);
		dup2(ms->fd_outorg, STDOUT_FILENO);
		args_free(ms);
	}
	ft_putstr_fd(MINISHELL, 1);
}

int		main(int argc, char *argv[], char *envp[])
{
	char		*line;
	int			i;
	t_env_list	*head;
	t_stock_str	ms;

	ms_init(&ms, argc, argv);
	head = init_copy_envp(envp);
	signal(SIGINT, (void *)sig_handler);
	signal(SIGQUIT, sig_quit);
	ft_putstr_fd(MINISHELL, 1);
	while ((i = get_next_line(0, &line)) > 0)
	{
		ms_print(&ms, line, &head);
		free(line);
	}
	free(line);
	if (i == 0)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	return (0);
}
