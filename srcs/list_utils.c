/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:27:57 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/21 21:27:58 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_env_key(char *env, char *key)
{
	int	count;
	int	key_cnt;

	count = 0;
	key_cnt = 0;
	while (env[count])
	{
		if (env[count] == '=' || env[count] == ' ')
			break ;
		count++;
	}
	while (key[key_cnt])
	{
		if (key[key_cnt] == '=' || key[key_cnt] == ' ')
			break ;
		key_cnt++;
	}
	if (count < key_cnt)
		count = key_cnt;
	if (ft_strncmp(env, key, count) == 0)
		return (1);
	return (0);
}

t_env_list	*find_env_key(t_env_list **head, char *key)
{
	t_env_list	*curr;

	curr = *head;
	while (curr->next)
	{
		curr = curr->next;
		if (is_env_key(curr->data, key))
			return (curr);
	}
	return (NULL);
}

int			lst_size(t_env_list *head)
{
	int			count;
	t_env_list	*curr;

	count = 0;
	curr = head;
	while (curr->next)
	{
		curr = curr->next;
		count++;
	}
	return (count);
}
