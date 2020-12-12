#include "minishell.h"

//TODO echo "$_" 나중에 하기

int	flag_check(t_stock_str *ms, char c)
{
	if (c == '\'')
		ms->sq_flag = 1;
	else if (c == '\"')
		ms->dq_flag = 1;
/*	else if (c == ';')
		ms->sc_flag = 1;
	else if (c == '|')
		ms->p_flag = 1;*/
	else
		return (1);
	return (0);
}
void	str_init(t_stock_str *ms)
{
	ms->w = 0;
	ms->h = 0;
	ms->p_flag = 0;//pipe flag
	ms->sc_flag = 0;//semicolon flag
	ms->sq_flag = 0; // single quarter
	ms->dq_flag = 0; // double quarter
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

void	sq_flag_parsing(t_stock_str *ms, char *line)
{
	while (line[ms->l_idx] != '\'')
		ms->args[ms->h][ms->w++] = line[ms->l_idx++];
	ms->sq_flag = 0;
}

// "ls'" ok
// ls' no
void	dq_flag_parsing(t_stock_str *ms, char *line, t_env_list *head)
{
	int j;
	char a[100];
	int brace; // 중괄호

	j = 0;
	brace = 0;
	while (line[ms->l_idx] != '\"')
	{
		if (line[ms->l_idx] == '\\')
		{
			ms->l_idx++;
			ms->args[ms->h][ms->w++] = line[ms->l_idx++];
		}
		else if (line[ms->l_idx] == '$')
		{
			ms->l_idx++;
			if (line[ms->l_idx] == '{')
			{
				ms->l_idx++;
				brace = 1;
			}
			//printf("line = %c\n", line[ms->l_idx]);
			while ((line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9') || (line[ms->l_idx] >= 'a' && line[ms->l_idx] <= 'z') || (line[ms->l_idx] >= 'A' && line[ms->l_idx] <= 'Z') || line[ms->l_idx] == '_' || line[ms->l_idx] == '=')
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
			//ms->l_idx = ms->l_idx - j; // 나중에 수정
			a[j] = '\0';
			//printf("a[j] = %s\n", a);
			//printf("envp = %s\n", envp[1]);
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
			//		printf("i = %d\n", i);
			//		printf("envp = %c\n", envp[1][hwyu]);
					ms->args[ms->h][ms->w] = test->data[hwyu];
					ms->w++;
					hwyu++;
				}
			}
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
void	dollor_parsing(t_stock_str *ms, char *line, t_env_list *head)
{
	int brace;
	int i;
	int j;
	char a[100];

	brace = 0;
	j = 0;
	ms->l_idx++;
	if (line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9')
	{
		i = line[ms->l_idx] - 48;
		argv_parsing(ms, i);
		return ;
	}
	else if (line[ms->l_idx] == '#')
	{
		ms->args[ms->h][ms->w] = ms->argc + 48 - 1;
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
	printf("line[ms->l_idx] = %c\n", line[ms->l_idx]);
	while ((line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9') || (line[ms->l_idx] >= 'a' && line[ms->l_idx] <= 'z') || (line[ms->l_idx] >= 'A' && line[ms->l_idx] <= 'Z') || line[ms->l_idx] == '_')
	{
		a[j] = line[ms->l_idx];
		j++;
		ms->l_idx++;
	}
	printf("line[ms->l_idx] = %c\n", line[ms->l_idx]);
	if (brace == 1)
	{
		while (line[ms->l_idx] != '}')
			ms->l_idx++;
		if (line[ms->l_idx] == '}')
			ms->l_idx++;
	}
	printf("line[ms->l_idx] = %c\n", line[ms->l_idx]);
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

int	parsing(char *line, t_stock_str *ms, t_env_list *head)
{
	int i;
	int j;
	// env " asdad"
	i = 0;
	j = 1 + space_check(line);
	//printf("hello\n");
	i = 0;
	printf("head = %s\n", head->next->data);
	ms->args = (char **)malloc(sizeof(char *) * (j + 1 + ms->argc));
	while (i < j + ms->argc)
		ms->args[i++] = (char *)malloc(sizeof(char) * 1000);
	i = 0;
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
			//j = flag_parsing(ms, line, k, cp_envp, j)
			//printf("line = %c\n", line[ms->l_idx]);
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
			if (line[ms->l_idx + 1] == '|' || line[ms->l_idx + 1] == ';')
				;
				else if (line[ms->l_idx + 1] != '\0')
			{
				ms->w = 0;
				ms->h++;
			}
		}
		ms->l_idx++;
	}
	write(1, "asdjasd\n", 8);
	ms->args_cnt = ms->h;
	ms->args[ms->h][ms->w] = '\0';
	ms->last_args = ft_strdup(ms->args[ms->h]);
	ms->args[ms->h + 1] = '\0';
	/*if (strncmp(ms->args[0], "echo", 4) == 0)
	{
		int hwyu = 0;
		printf("\n-------------echo----------------\n");
		while (ms->args[hwyu])
		{
			hwyu++;
			if (ms->args[hwyu])
				printf("%s ", ms->args[hwyu]);
		}
		printf("\n-------------echo----------------\n");
		printf("p_flag = %d\n", ms->p_flag);
		printf("sc_flag = %d\n", ms->sc_flag);
		printf("l_idx = %d\n", ms->l_idx);
		printf("sq_flag = %d\n", ms->sq_flag);
		printf("dq_flag = %d\n", ms->dq_flag);
		printf("ms->l_idx = %c\n", line[ms->l_idx]);
	}*/
	return (0);
}
