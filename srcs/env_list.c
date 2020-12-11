#include "minishell.h"

//env key값 체크하는 것. 1이면 키값이 있다.
int	is_env_key(char *env, char *del)
{
	int	count;
	int	del_count;

	count = 0;
	del_count = 0;
	while (env[count])
	{
		if (env[count] == '=' || env[count] == ' ')
			break;
		count++;
	}
	while (del[del_count])
	{
		if (del[del_count] == '=' || del[del_count] == ' ')
			break;
		del_count++;
	}
	if (count < del_count)
		count = del_count;
	if (ft_strncmp(env, del, count) == 0)
		return (1);
	return (0);
}

t_env_list	*find_env_key(t_env_list **head, char *s)
{
	t_env_list	*curr;

	curr = *head;
	while (curr->next)
	{
		curr = curr->next;
		if (is_env_key(curr->data, s))
			return (curr);
	}
	return (NULL);
}

void	delete_node(t_env_list **head, char *s)
{
	t_env_list *curr;

	if ((curr = find_env_key(head, s)) != 0)
	{
		printf("check %s\n", curr->data);
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
	int	i;

	i = 0;
	head = (t_env_list *)malloc(sizeof(t_env_list));
	if (head == NULL)
		return (0);
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
