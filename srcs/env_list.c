#include "minishell.h"

//env key값 체크하는 것. 1이면 키값이 있다.
int	is_env_key(char *env, char *del)
{
	int	count;

	count = 0;
	while (env[count])
	{
		if (env[count] == '=' || env[count] == ' ')
		{
			count--;
			break;
		}
		count++;
	}
	if (count < (int)ft_strlen(del))
		count = (int)ft_strlen(del);
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
	if ((curr = find_env_key(head, s)))
	{
		curr->prev->next = curr->next;
		if (curr->next)
			curr->next->prev = curr->prev;
		free(curr->data);
		free(curr);
	}
	/*
	//다음 노드가 널이 아니면 반복시키면서 그 노드로 이동
	curr = *head;
	while (curr->next)
	{
		curr = curr->next;
		if (is_env_key(curr->data, s))
		{
			printf("find index \n");
			curr->prev->next = curr->next;
			if (curr->next)
				curr->next->prev = curr->prev;
			free(curr->data);
			free(curr);

			printf("free data and pointer\n");
			return ;
		}
	}
*/
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

/*
int	main(int argc, char *argv[], char *envp[])
{
	t_env_list *head;//user=" " printf("ft_sf(head, "USER")")

	head = init_copy_envp(envp);
	printf_list(head);
	*/

	/*
	t_env_list *node;
	int	i;

	head = (t_env_list *)malloc(sizeof(t_env_list));
	if (head == NULL)
		return (0);
	head->prev = NULL;
	head->next = NULL;

	i = 0;
	while (envp[i])
	{
		node = create_node(envp[i]);
		add_new_node(&head, node);
//		printf("%d, \n", i);
//		printf("%s\n", node->data);
		i++;
	}
	*/
	//printf("head : %s\n", head->data);
	//printf("head : %s\n", head->next->data);

	/*
	while (head)
	{
		printf("%s\n", head->data);
		head = head->next;
	}
	*/
//	export_print(head);

//	printf_list(head);

	/*
	node = create_node("abc");
	add_new_node(&head, node);
	node = create_node("abcdef");
	add_new_node(&head, node);
	printf_list(head);
	delete_node(&head, "abc");
	delete_node(&head, "LESS");
	delete_node(&head, "abcdef");
	printf_list(head);
	*/
