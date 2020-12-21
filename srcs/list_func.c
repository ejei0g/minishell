/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:27:51 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/21 21:27:52 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*create_node(char *data)
{
	t_env_list	*new_node;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	if (new_node == NULL)
		return (NULL);
	new_node->data = ft_strdup(data);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void		add_new_node(t_env_list **head, t_env_list *new_node)
{
	t_env_list	*curr;

	if (!head || !new_node)
		return ;
	curr = *head;
	if (*head == NULL)
		*head = new_node;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new_node;
		new_node->prev = curr;
	}
}

void		delete_node(t_env_list **head, char *s)
{
	t_env_list	*curr;

	if ((curr = find_env_key(head, s)) != 0)
	{
		curr->prev->next = curr->next;
		if (curr->next)
			curr->next->prev = curr->prev;
		free(curr->data);
		free(curr);
	}
	return ;
}

t_env_list	*init_copy_envp(char **envp)
{
	t_env_list	*head;
	t_env_list	*node;
	int			i;

	i = 0;
	head = (t_env_list *)malloc(sizeof(t_env_list));
	if (head == NULL)
		return (0);
	head->data = NULL;
	head->prev = NULL;
	head->next = NULL;
	while (envp[i])
	{
		node = create_node(envp[i]);
		add_new_node(&head, node);
		i++;
	}
	return (head);
}

void		free_env_list(t_env_list **env)
{
	t_env_list	*curr;
	t_env_list	*tmp;

	if (!env)
		return ;
	curr = *env;
	tmp = curr;
	while (curr != NULL)
	{
		tmp = curr->next;
		if (curr->data != NULL)
			free(curr->data);
		free(curr);
		curr = tmp;
	}
	*env = NULL;
	return ;
}
