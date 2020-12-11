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

int	sq_flag_parsing(t_stock_str *ms, char *line, int k, int j)
{
	while (line[ms->l_idx] != '\'')
		ms->args[k][j++] = line[ms->l_idx++];
	ms->sq_flag = 0;
	return (j);
}

// "ls'" ok
// ls' no
int	dq_flag_parsing(t_stock_str *ms, char *line, int k, int i, t_env_list *head)
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
			ms->args[k][i++] = line[ms->l_idx++];
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
					ms->args[k][i] = test->data[hwyu];
					i++;
					hwyu++;
				}
			}
		}
		else
			ms->args[k][i++] = line[ms->l_idx++];
	}
	ms->dq_flag = 0;
	return (i);
}
int	dollor_parsing(t_stock_str *ms, char *line, int k, int i, t_env_list *head)
{
	int brace;
	int j;
	char a[100];

	brace = 0;
	j = 0;
	ms->l_idx++;
	if (line[ms->l_idx] == '{')
	{
		ms->l_idx++;
		brace = 1;
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
			ms->args[k][i] = test->data[hwyu];
			i++;
			hwyu++;
		}
	}
	ms->l_idx--;
	return (i);
}

int	parsing(char *line, t_stock_str *ms, t_env_list *head)
{
	int i;
	int j;
	int k;
	// env " asdad"
	i = 0;
	j = 0;
	k = 0;

	j = 1 + space_check(line);
	//printf("hello\n");
	i = 0;
	printf("head = %s\n", head->next->data);
	ms->args = (char **)malloc(sizeof(char *) * (j + 1));
	while (i < j)
		ms->args[i++] = (char *)malloc(sizeof(char) * 1000);
	j = 0;
	i = 0;
	while (line[ms->l_idx])
	{
		if (ms->sq_flag == 1)
			j = sq_flag_parsing(ms, line, k, j);
		else if (ms->dq_flag == 1)
			j = dq_flag_parsing(ms, line, k, j, head);
		else if (flag_check(ms, line[ms->l_idx]) == 0)
			;
		else if (line[ms->l_idx] != ' ')
		{
			//j = flag_parsing(ms, line, k, cp_envp, j)
			//printf("line = %c\n", line[ms->l_idx]);
			if (line[ms->l_idx] == '\\')
			{
				ms->l_idx++;
				ms->args[k][j] = line[ms->l_idx];
				j++;
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
				j = dollor_parsing(ms, line, k, j, head);
			else
			{
				ms->args[k][j] = line[ms->l_idx];
				j++;
			}
		}
		else if (line[ms->l_idx] == ' ')
		{
			ms->args[k][j] = '\0';
			while (line[ms->l_idx + 1] == ' ')
				ms->l_idx++;
			if (line[ms->l_idx + 1] == '|' || line[ms->l_idx + 1] == ';')
				;
				else if (line[ms->l_idx + 1] != '\0')
			{
				j = 0;
				k++;
			}
		}
		ms->l_idx++;
	}
	ms->args[k][j] = '\0';
	ms->args[k + 1] = '\0';
	
	if (strncmp(ms->args[0], "echo", 4) == 0)
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
	}
	return (0);
}
