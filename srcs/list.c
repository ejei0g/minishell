#include "minishell.h"

//노드 생성. data(envp[i])를 복제했으므로 프리필요.
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

void	add_new_node(t_env_list **head, t_env_list *new_node)
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

int	count_lst_size(t_env_list *head)
{
	int	count;
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
//TODO: env, export 에서 _=<dir>은 항상 고정값. 주의 $$$$@@@###@@#!@#
//export에서 출력도 되면 안되고, 수정도 되서는 안됨. 
		if(ft_strncmp(s[i], "_=", 2) != 0)
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
	int	i;
	int	max_index;
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

void	free_cp_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	export_print(t_env_list *head)
{
	t_env_list	*curr;
	int	i;
	char	**cp_envp;

	i = 0;
	curr = head;
	//alloc;
	cp_envp = (char **)malloc(sizeof(char *) * (count_lst_size(head) + 1));
	if (cp_envp == NULL)
		return ;
	//copy;
	while (curr->next)
	{
		curr = curr->next;
		cp_envp[i] = ft_strdup(curr->data);
		i++;
	}
	cp_envp[i] = '\0';
	//sorting and print
	ft_sort_print(cp_envp);
	//free;
	free_cp_envp(cp_envp);
}

//delete
//insert
