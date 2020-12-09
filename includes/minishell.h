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

int     flag_check(t_stock_str *ms, char c);
int     parsing(char *line, t_stock_str *ms);
void    str_init(t_stock_str *ms);
int     flag_check(t_stock_str *ms, char c);

#endif
