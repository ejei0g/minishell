#ifndef _MINISHELL_H
# define _MINISHELL_H

#include <stdio.h>//printf 때문에 지워야함 나중에
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"

typedef struct	s_stock_str {
	//char	*args[10000];//arguments
	char	**args;//arguments
	//args[0] == cmd; 
	char	**envs;//enviroments
	int		p_flag;//pipe flag
	int		sc_flag;//semicolon flag
	int		l_idx; //line index
	int		sq_flag; // single quarter
	int		dq_flag; // double quarter
}		t_stock_str;

typedef struct	s_env_list
{
	char	*data;
	struct s_env_list	*next;
	struct s_env_list	*prev;
}		t_env_list;

int     flag_check(t_stock_str *ms, char c);
int     parsing(char *line, t_stock_str *ms, char **cp_envp);
void    str_init(t_stock_str *ms);
int     flag_check(t_stock_str *ms, char c);

//----------------env list-, export, env, unset

t_env_list	*create_node(char *data);
void	add_new_node(t_env_list **head, t_env_list *new_node);
int	count_lst_size(t_env_list *head);

void	printf_list(t_env_list *head);//나중에 삭제

void	export_print(t_env_list *head);
void	ft_sort_print(char **s);
void	print_sorting_arr(char **s);

int	is_env_key(char *env, char *del);
t_env_list	*find_env_key(t_env_list **head, char *s);
void	delete_node(t_env_list **head, char *s);
t_env_list	*init_copy_envp(char **envp);
//----------------env list-, export, env, unset

#endif
