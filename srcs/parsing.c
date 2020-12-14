#include "minishell.h"

//TODO echo "$_" 나중에 하기
// $1 asd 이렇게 했을떄 $1이 널값이면 앞에 스페이스가 추가되는거 수정해야됨
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

int		all_argv_parsing(t_stock_str *ms, char *line)
{
	int i;

	i = 1;
	if (line[ms->l_idx] == '*' || line[ms->l_idx] == '@')
	{
		while (i < ms->argc)
		{
			argv_parsing(ms, i++);
			if (ms->argv[i] == NULL)
			{
				ms->l_idx++;
				return 0;
			}
			ms->args[ms->h++][ms->w] = '\0';
			ms->w = 0;
		}
		ms->l_idx++;
		return 0;
	}
	return 1;
}

int		dollor_argcv(t_stock_str *ms, char *line, int i)
{
	if (line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9')
	{
		while (line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9')
			i = i * 10 + line[ms->l_idx++] - 48;
		argv_parsing(ms, i);
		return 0;
	}
	else if (line[ms->l_idx] == '#')
	{
		ms->args[ms->h][ms->w++] = ms->argc + 48 - 1;
		return 0;
	}
	if (all_argv_parsing(ms, line) == 0)
		return (0);
	return (1);
}

int		dollor_parsing2(t_stock_str *ms, char *line, int brace)
{
	if (line[ms->l_idx] == '{')
	{
		ms->l_idx++;
		brace = 1;
	}
	if (dollor_argcv(ms, line, 0) == 0)
	{
		if (brace != 1) // echo ${0asd} 에러처리
			ms->l_idx--;
		return -1;
	}
	if (!((line[ms->l_idx] >= 'a' && line[ms->l_idx] <= 'z') || (line[ms->l_idx] >= 'A' && line[ms->l_idx] <= 'Z') || line[ms->l_idx] == '_'))
	{
		ms->args[ms->h][ms->w++] = '$';
		ms->l_idx--;
		return -1;
	}
	return (brace);
}

void	env_parsing(t_stock_str *ms, t_env_list *head, char a[100])
{
	int i;

	i = 0;
	t_env_list *test;
	test = find_env_key(&head, a);
	if (test != NULL)
	{
		while (test->data[i] != '=')
			i++;
		i++;
		while (test->data[i])
		{
			ms->args[ms->h][ms->w] = test->data[i];
			ms->w++;
			i++;
		}
	}
	ms->l_idx--;
}

void	dollor_parsing(t_stock_str *ms, char *line, t_env_list *head)
{
	int brace;
	int j;
	char a[100];

	brace = 0;
	j = 0;
	ms->l_idx++;
	brace = dollor_parsing2(ms, line, brace);
	if (brace == -1)
		return ;
	while ((line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9') ||
			(line[ms->l_idx] >= 'a' && line[ms->l_idx] <= 'z') ||
			(line[ms->l_idx] >= 'A' && line[ms->l_idx] <= 'Z') || line[ms->l_idx] == '_')
		a[j++] = line[ms->l_idx++];
	a[j] = '\0';
	if (brace == 1)
	{
		while (line[ms->l_idx] != '}')
			ms->l_idx++;
		ms->l_idx++;
	}
	env_parsing(ms, head, a);
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

int		rdir_flag_setting(t_stock_str *ms, char *line)
{
	if (line[ms->l_idx] == '>' && line[ms->l_idx + 1] == '>')
	{
		ms->l_idx = ms->l_idx + 2;
		return (1);
	}
	else if (line[ms->l_idx] == '>')
	{
		ms->l_idx = ms->l_idx + 1;
		return (2);
	}
	else if (line[ms->l_idx] == '<')
	{
		ms->l_idx = ms->l_idx + 1;
		return (3);
	}
	return (0);
}

void	rdir_fd_dup(t_stock_str *ms, int rdir_flag)
{
	int	fd = 0;

	if (rdir_flag == 1)
		fd = open(ms->file_name, O_WRONLY | O_CREAT | O_APPEND);
	else if (rdir_flag == 2)
		fd = open(ms->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (rdir_flag == 3)
		fd = open(ms->file_name, O_RDONLY);
	if (rdir_flag == 3)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
}

void	redirect_parsing(t_stock_str *ms, char *line)
{
	int	i = 0;
	int	rdir_flag;
	char	filename[100];
	int	cp_l_idx;

	i = 0;
	cp_l_idx = 0;
	rdir_flag = rdir_flag_setting(ms, line);
	while (line[ms->l_idx] == ' ' && line[ms->l_idx] != '\0')
		ms->l_idx++;
	cp_l_idx = ms->l_idx;
	while (line[ms->l_idx] != ' ' && line[ms->l_idx] != '\0')
		filename[i++] = line[ms->l_idx++];
	filename[i] = '\0';
	ms->file_name = ft_strdup(filename);
	if (ft_strncmp(ms->args[0], "echo", 4) == 0)
		return ;
	rdir_fd_dup(ms, rdir_flag);
	if (rdir_flag == 3)
		ms->l_idx = cp_l_idx;
	ms->l_idx--;
}

int		p_sc_flag_parsing(t_stock_str *ms, char *line)
{
	if (line[ms->l_idx] == '|')
	{
		ms->p_flag = 1;
		ms->l_idx++;
		while (line[ms->l_idx] == ' ')
			ms->l_idx++;
		return (0);
	}
	else if (line[ms->l_idx] == ';')
	{
		ms->sc_flag = 1;
		ms->l_idx++;
		while (line[ms->l_idx] == ' ')
			ms->l_idx++;
		return (0);
	}
	return (-1);
}

int	parsing_n_apace(t_stock_str *ms, char *line, t_env_list *head)
{
	if (line[ms->l_idx] == '\\')
		ms->args[ms->h][ms->w++] = line[++ms->l_idx];
	else if (p_sc_flag_parsing(ms, line) == 0)
		return (-1);
	else if (line[ms->l_idx] == '$')
		dollor_parsing(ms, line, head);
	else if (line[ms->l_idx] == '>' || line[ms->l_idx] == '<')
		redirect_parsing(ms, line);
	else
		ms->args[ms->h][ms->w++] = line[ms->l_idx];
	return (0);
}

void	parsing_is_space(t_stock_str *ms, char *line)
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

void	line_parsing(char *line, t_stock_str *ms, t_env_list *head)
{
	while (line[ms->l_idx])
	{
		if (ms->sq_flag == 1)
			sq_flag_parsing(ms, line);
		else if (ms->dq_flag == 1)
			dq_flag_parsing(ms, line, head);
		else if (flag_check(ms, line[ms->l_idx]) == 0)
			;
		else if (line[ms->l_idx] != ' ')
		{
			if (parsing_n_apace(ms, line, head) == -1)
				break;
		}
		else if (line[ms->l_idx] == ' ')
			parsing_is_space(ms, line);
		ms->l_idx++;
	}
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
	line_parsing(line, ms, head);
	ms->args_cnt = ms->h;
	ms->args[ms->h][ms->w] = '\0';
	ms->last_args = ft_strdup(ms->args[ms->h]);
	ms->args[ms->h + 1] = '\0';
	return (0);
}
