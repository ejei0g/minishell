#ifndef _LIST_H
# define _LIST_H

#include <stdlib.h>
#include <stdio.h>

typedef struct	s_list
{
	char	*data; //
	struct s_list	*next;
	struct s_list	*prev;
}		t_list;

int	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s, size_t n);
char	*ft_strdup(const char *s1);



t_list	*create_node(char *data);
void	add_new_node(t_list **head, t_list *new_node);
int	count_lst_size(t_list *head);

void	printf_list(t_list *head);//나중에 삭제

void	export_print(t_list *head);
void	ft_sort_print(char **s);
void	print_sorting_arr(char **s);

int	is_env_key(char *env, char *del);
t_list	*find_env_key(t_list **head, char *s);
void	delete_node(t_list **head, char *s);
t_list	*init_copy_envp(char **envp);


#endif
