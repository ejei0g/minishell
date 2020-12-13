#include "minishell.h"

//TODO echo "$_" 나중에 하기
void	argv_parsing(t_stock_str *ms, int i);

int	flag_check(t_stock_str *ms, char c)
{
	if (c == '\'')
		ms->sq_flag = 1;
	else if (c == '\"')
		ms->dq_flag = 1;
	else
		return (1);
	return (0);
}
void	str_init(t_stock_str *ms)
{
	ms->w = 0; //args_width
	ms->h = 0; //args_height
	ms->p_flag = 0;//pipe flag
	ms->sc_flag = 0;//semicolon flag
	ms->sq_flag = 0; // single quarter
	ms->dq_flag = 0; // double quarter
	ms->null_flag = 0;
}

int	space_check(char *line)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (line[0] == '\0')
		return (-1);
	while (line[i])
	{
		if (line[i] == ' ' && line[i - 1] != ' ')
			j++;
		i++;
	}
	return (j);
}
void	dollor_parsing(t_stock_str *ms, char *line, t_env_list *head)
{
	int brace;
	int i;
	int j;
	char a[100];

	brace = 0;
	i = 0;
	j = 0;
	ms->l_idx++;
	if (line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9')
	{
		i = line[ms->l_idx++] - 48;
		ms->l_idx--;
		argv_parsing(ms, i);
		return ;
	}
	else if (line[ms->l_idx] == '#')
	{
		ms->args[ms->h][ms->w++] = ms->argc + 48 - 1;
		return ;
	}
	i = 1;
	if (line[ms->l_idx] == '*' || line[ms->l_idx] == '@')
	{
		while (i < ms->argc)
		{
			argv_parsing(ms, i);
			i++;
			if (ms->argv[i] == NULL)
				return ;
			ms->args[ms->h][ms->w] = '\0';
			ms->h++;
			ms->w = 0;
		}
		return ;
	}
	if (line[ms->l_idx] == '{')
	{
		ms->l_idx++;
		brace = 1;
	}
	else if (!((line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9') || (line[ms->l_idx] >= 'a' && line[ms->l_idx] <= 'z') || (line[ms->l_idx] >= 'A' && line[ms->l_idx] <= 'Z') || line[ms->l_idx] == '_'))
	{
		ms->args[ms->h][ms->w] = '$';
		ms->w++;
		ms->l_idx--;
		return ;
	}
	if (line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9')
	{
		i = 0;
		while (line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9')
			i = i * 10 + line[ms->l_idx++] - 48;
		argv_parsing(ms, i);
	}
	if (line[ms->l_idx] == '*' || line[ms->l_idx] == '@')
        {
		i = 0;
                while (i < ms->argc)
                {
                        argv_parsing(ms, i);
                        i++;
                        if (ms->argv[i] != NULL)
			{
                        ms->args[ms->h][ms->w] = '\0';
                        ms->h++;
                        ms->w = 0;
			}
                }
        }
	while ((line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9') || (line[ms->l_idx] >= 'a' && line[ms->l_idx] <= 'z') || (line[ms->l_idx] >= 'A' && line[ms->l_idx] <= 'Z') || line[ms->l_idx] == '_')
	{
		a[j] = line[ms->l_idx];
		j++;
		ms->l_idx++;
	}
	if (brace == 1)
	{
		while (line[ms->l_idx] != '}')
			ms->l_idx++;
		if (line[ms->l_idx] == '}')
			ms->l_idx++;
	}
	a[j] = '\0';
	t_env_list *test;
	test = find_env_key(&head, a);
	if (test != NULL)
	{
		int hwyu = 0;
		while (test->data[hwyu] != '=')
			hwyu++;
		hwyu++;
		while (test->data[hwyu])
		{
			ms->args[ms->h][ms->w] = test->data[hwyu];
			ms->w++;
			hwyu++;
		}
	}
	ms->l_idx--;
}

void	sq_flag_parsing(t_stock_str *ms, char *line)
{
	while (line[ms->l_idx] != '\'')
		ms->args[ms->h][ms->w++] = line[ms->l_idx++];
	ms->sq_flag = 0;
}

void	dq_flag_parsing(t_stock_str *ms, char *line, t_env_list *head)
{
	while (line[ms->l_idx] != '\"')
	{
		if (line[ms->l_idx] == '\\')
		{
			ms->l_idx++;
			ms->args[ms->h][ms->w++] = line[ms->l_idx++];
		}
		else if (line[ms->l_idx] == '$')
		{
			dollor_parsing(ms, line, head);
			ms->l_idx++;
		}
		else
			ms->args[ms->h][ms->w++] = line[ms->l_idx++];
	}
	ms->dq_flag = 0;
}

void	argv_parsing(t_stock_str *ms, int i)
{
	int j;

	j = 0;
	if (ms->argv[i] == NULL)
		return ;
	while (ms->argv[i][j])
		ms->args[ms->h][ms->w++] = ms->argv[i][j++];
	return ;
}

int	null_flag(t_stock_str *ms, char *line)
{
	int i;

	if (ms->null_flag == -1)
		return (-1);
	if (ft_strncmp(ms->args[0], "echo", 4) != 0)
	{
		if (ms->null_flag == 0)
			ms->null_flag = -1;
		return (-1);
	}
	i = ms->l_idx;
	ms->l_idx++;
	if (line[ms->l_idx] == '-' && line[ms->l_idx + 1] == 'n')
	{
		ms->l_idx++;
		while (line[ms->l_idx] == 'n')
			ms->l_idx++;
		if (line[ms->l_idx] == ' ' || line[ms->l_idx] == '\0')
		{
			ms->null_flag = 1;
			return (0);
		}
	}
	ms->l_idx = i;
	if (ms->null_flag == 0)
		ms->null_flag = -1;
	return (-1);
}

void	redirect_parsing(t_stock_str *ms, char *line)
{
	int	i = 0;
	int	fd = 0;
//	int	fd_copy;
	int	rdir_flag = 0;
	char	filename[100];
	int	cp_l_idx;

	i = 0;
	cp_l_idx = 0;
	printf("redirecion\n");
//	fd_copy = fd;
	if (line[ms->l_idx] == '>' && line[ms->l_idx + 1] == '>')
	{
		rdir_flag = 1;
		ms->l_idx = ms->l_idx + 2;
	}
	else if (line[ms->l_idx] == '>')
	{
		ms->l_idx = ms->l_idx + 1;
		rdir_flag = 2;
	}
	else if (line[ms->l_idx] == '<')
	{
		ms->l_idx = ms->l_idx + 1;
		rdir_flag = 3;
	}
	while (line[ms->l_idx] == ' ' && line[ms->l_idx] != '\0')
		ms->l_idx++;
	cp_l_idx = ms->l_idx;
	while (line[ms->l_idx] != ' ' && line[ms->l_idx] != '\0')
		filename[i++] = line[ms->l_idx++];
	filename[i] = '\0';
	ms->file_name = ft_strdup(filename);
	if (ft_strncmp(ms->args[0], "echo", 4) == 0)
		return ;
	if (rdir_flag == 1)
		fd = open(ms->file_name, O_WRONLY | O_CREAT | O_APPEND);
	if (rdir_flag == 2)
		fd = open(ms->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (rdir_flag == 3)
		fd = open(ms->file_name, O_RDONLY);
	if (rdir_flag == 3)
	{
		dup2(fd, STDIN_FILENO);
		ms->l_idx = cp_l_idx;
	}
	else
		dup2(fd, STDOUT_FILENO);
	printf("cp = %d\n", cp_l_idx);
	ms->l_idx--;
}

int	parsing(char *line, t_stock_str *ms, t_env_list *head)
{
	int i;
	int j;
	i = 0;
	j = 1 + space_check(line);
	ms->args = (char **)malloc(sizeof(char *) * (j + 1 + ms->argc));
	while (i < j + ms->argc)
		ms->args[i++] = (char *)malloc(sizeof(char) * 1000);
	i = 0;
	while (line[ms->l_idx])
	{
	//	printf("line = %c\n", line[ms->l_idx]);
	//	if (null_flag(ms, line) == 0)
	//		;
		if (ms->sq_flag == 1)
			sq_flag_parsing(ms, line);
		else if (ms->dq_flag == 1)
			dq_flag_parsing(ms, line, head);
		else if (flag_check(ms, line[ms->l_idx]) == 0)
			;
		else if (line[ms->l_idx] != ' ')
		{
			if (line[ms->l_idx] == '\\')
			{
				ms->l_idx++;
				ms->args[ms->h][ms->w] = line[ms->l_idx];
				ms->w++;
			}
			else if (line[ms->l_idx] == '|')
			{
				ms->p_flag = 1;
				ms->l_idx++;
				while (line[ms->l_idx] == ' ')
					ms->l_idx++;
				break ;
			}
			else if (line[ms->l_idx] == ';')
			{
				ms->sc_flag = 1;
				ms->l_idx++;
				while (line[ms->l_idx] == ' ')
					ms->l_idx++;
				break ;
			}
			else if (line[ms->l_idx] == '$')
				dollor_parsing(ms, line, head);
			else if (line[ms->l_idx] == '>' || line[ms->l_idx] == '<')
			{
				write(1, "1q2w3e4r\n", 9);
				redirect_parsing(ms, line);
			}
			else
			{
				ms->args[ms->h][ms->w] = line[ms->l_idx];
				ms->w++;
			}
		}
		else if (line[ms->l_idx] == ' ')
		{
			ms->args[ms->h][ms->w] = '\0';
			while (line[ms->l_idx + 1] == ' ')
				ms->l_idx++;
			while (null_flag(ms, line) == 0)
				;
			while (line[ms->l_idx + 1] == ' ')
				ms->l_idx++;
			if (line[ms->l_idx + 1] == '|' || line[ms->l_idx + 1] == ';' || line[ms->l_idx + 1] == '>')
				;
			else if (line[ms->l_idx + 1] != '\0')
			{
				ms->w = 0;
				ms->h++;
			}
		}
		ms->l_idx++;
	}
	ms->args_cnt = ms->h;
	ms->args[ms->h][ms->w] = '\0';
	ms->last_args = ft_strdup(ms->args[ms->h]);
	ms->args[ms->h + 1] = '\0';
	return (0);
}
