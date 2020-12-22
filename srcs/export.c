/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:27:28 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/22 16:59:02 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_key(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
	{
		if (s[i] == '\0')
			return ;
		write(1, &s[i], 1);
		i++;
	}
	write(1, &s[i++], 1);
	write(1, "\"", 1);
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\"", 1);
}

void	print_sorting_arr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strncmp(s[i], "_=", 2) != 0)
		{
			ft_putstr_fd("declare -x ", 1);
			print_env_key(s[i]);
			write(1, "\n", 1);
		}
		i++;
	}
}

void	ft_sort_print(char **s)
{
	int		i;
	int		max_index;
	char	*tmp;

	i = 0;
	max_index = 0;
	while (s[max_index])
		max_index++;
	while (i < max_index - 1)
	{
		if (ft_strncmp(s[i], s[i + 1], ft_strlen(s[i])) > 0)
		{
			tmp = ft_strdup(s[i]);
			free(s[i]);
			s[i] = s[i + 1];
			s[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	print_sorting_arr(s);
}

void	export_print(t_env_list *head)
{
	t_env_list	*curr;
	int			i;
	char		**cp_envp;

	i = 0;
	curr = head;
	cp_envp = (char **)malloc(sizeof(char *) * (lst_size(head) + 1));
	if (cp_envp == NULL)
		return ;
	while (curr->next)
	{
		curr = curr->next;
		cp_envp[i] = ft_strdup(curr->data);
		i++;
	}
	cp_envp[i] = NULL;
	ft_sort_print(cp_envp);
	free_envp_arr(cp_envp);
}

void	export_add(t_stock_str ms, t_env_list **env)
{
	t_env_list	*tmp;
	int			i;

	i = 1;
	while (ms.args[i])
	{
		if (ft_strncmp(ms.args[i], "_=", 2) == 0)
			;
		else if (ms.args[i][0] == '=')
			;
		else if ((tmp = find_env_key(env, ms.args[i])) != 0)
		{
			free(tmp->data);
			tmp->data = ft_strdup(ms.args[i]);
		}
		else
		{
			tmp = create_node(ms.args[i]);
			add_new_node(env, tmp);
		}
		i++;
	}
}
