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

typedef struct	s_stock_str {
	char	*cmd; //command
	char	**args;//arguments
	//args[0] == cmd; 
	char	**envs;//enviroments
	int	p_flag;//pipe flag
	int	sc_flag;//semicolon flag
	int	line_index; //line index
}		t_stock_str;

#endif
