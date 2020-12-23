/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 16:50:45 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/23 22:36:50 by hwyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include "get_next_line.h"
# include "libft.h"
# define MINISHELL	"\033[34m 42Seoul@$:\033[0m"
# define PWD_SIZE	10000
# define ORIGIN		"\033[0m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define PURPLE		"\033[35m"
# define BLUEGREEN	"\033[36m"
# define ECHO		"echo"
# define CD			"cd"
# define PWD		"pwd"
# define EXPORT		"export"
# define UNSET		"unset"
# define ENV		"env"
# define EXIT		"exit"
# define INVALID	"!@?$%^-+{}[],./:"

int	g_err_num;

typedef struct	s_stock_str {
	char		**args;
	char		*last_args;
	int			w;
	int			h;
	int			argc;
	char		**argv;
	int			args_cnt;
	char		*file_name;
	int			fd_inorg;
	int			fd_outorg;
	char		**envs;
	int			p_flag;
	int			sc_flag;
	int			l_idx;
	int			sq_flag;
	int			dq_flag;
	int			null_flag;
	int			fd_flag;
	int			err;
}				t_stock_str;

typedef struct	s_el
{
	char		*data;
	struct s_el	*next;
	struct s_el	*prev;
}				t_env_list;

int				parsing(char *line, t_stock_str *ms, t_env_list *head);
int				flag_check(t_stock_str *ms, char c);
void			str_init(t_stock_str *ms);
void			args_free(t_stock_str *ms);
int				rdir_fd_dup(t_stock_str *ms, int rdir_flag);
int				rdir_flag_setting(t_stock_str *ms, char *line);
void			sq_flag_parsing(t_stock_str *ms, char *line);
void			dq_flag_parsing(t_stock_str *ms, char *line, t_env_list *head);
int				null_flag(t_stock_str *ms, char *line, int i);
int				p_sc_flag_parsing(t_stock_str *ms, char *line);
void			env_parsing(t_stock_str *ms, t_env_list *head, char a[100]);
int				all_argv_parsing(t_stock_str *ms, char *line);
void			argv_parsing(t_stock_str *ms, int i);
void			str_init(t_stock_str *ms);
void			args_free(t_stock_str *ms);
int				flag_check(t_stock_str *ms, char c);
int				space_check(char *line);
int				parsing_n_apace(t_stock_str *ms, char *line, t_env_list *head);
void			parsing_is_space(t_stock_str *ms, char *line);
void			line_parsing(char *line, t_stock_str *ms, t_env_list *head);
void			dollor_parsing(t_stock_str *ms, char *line, t_env_list *head);
int				dollor_parsing2(t_stock_str *ms, char *line, int brace);
int				dollor_argcv(t_stock_str *ms, char *line, int i);
int				redirect_parsing(t_stock_str *ms, char *line);
void			pipe_func(t_stock_str *ms, t_env_list **head);
void			ms_init(t_stock_str *ms, int argc, char *argv[]);
t_env_list		*init_copy_envp(char **envp);
t_env_list		*create_node(char *data);
void			add_new_node(t_env_list **head, t_env_list *new_node);
void			delete_node(t_env_list **head, char *s);
int				lst_size(t_env_list *head);
void			free_env_list(t_env_list **env);
void			export_add(t_stock_str *ms, t_env_list **env);
void			export_print(t_env_list *head);
void			ft_sort_print(char **s);
void			print_sorting_arr(char **s);
void			free_envp_arr(char **envp);
t_env_list		*find_env_key(t_env_list **head, char *s);
int				is_env_key(char *env, char *del);
void			ms_proc(t_stock_str *ms, t_env_list **env);
void			ft_ms_echo(t_stock_str *ms);
void			ft_ms_cd(t_stock_str *ms, t_env_list **env);
void			ft_ms_pwd(t_stock_str *ms);
void			ft_ms_export(t_stock_str *ms, t_env_list **env);
void			ft_ms_unset(t_stock_str *ms, t_env_list **env);
void			ft_ms_env(t_stock_str *ms, t_env_list *env);
void			ft_ms_exit(t_env_list **env);
void			ft_ms_else(t_stock_str *ms, t_env_list **env);
void			err_invalid(t_stock_str *ms, int i);
char			*err_path_dir(void);
int				is_cmd(char *s1, char *s2);
int				invalid_id(char *s);
int				chk_invalid(char *s1, char *s2, int len);

#endif
