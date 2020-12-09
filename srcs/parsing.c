#include "minishell.h"

int	flag_check(t_stock_str *ms, char c)
{
	if (c == '\'')
		ms->sq_flag = 1;
	else if (c == '\"')
		ms->dq_flag = 1;
	else if (c == ';')
		ms->sc_flag = 1;
	else if (c == '|')
		ms->p_flag = 1;
	else
		return (1);
	return (0);
}
void	str_init(t_stock_str *ms)
{
//	int i;
//	int j;

//	i = 0;
	/*while (ms->args[i])
	{
		j = 0;
		while (ms->args[i][j])
		{
			ms->args[i][j] = '\0';
			j++;
		}
		i++;
	}*/
	ms->p_flag = 0;//pipe flag
	ms->sc_flag = 0;//semicolon flag
	ms->l_idx = 0; //line index
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

int	sq_flag_parsing(t_stock_str *ms, char *line, int k)
{
	int i;

	i = 0;
	while (line[ms->l_idx] != '\'')
		ms->args[k][i++] = line[ms->l_idx++];
	ms->sq_flag = 0;
	return (i);
}

int	parsing(char *line, t_stock_str *ms)
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
	ms->args = (char **)malloc(sizeof(char *) * (j + 1));
	while (i < j)
		ms->args[i++] = (char *)malloc(sizeof(char) * 1000);
	j = 0;
	i = 0;
	while (line[ms->l_idx])
	{
		if (ms->sq_flag == 1)
			j = sq_flag_parsing(ms, line, k);
		else if (ms->dq_flag == 1)
			j = sq_flag_parsing(ms, line, k);
		else if (flag_check(ms, line[ms->l_idx]) == 0)
			;
		else if (line[ms->l_idx] != ' ')
		{
			ms->args[k][j] = line[ms->l_idx];
			j++;
		}
		else if (line[ms->l_idx] == ' ')
		{
			ms->args[k][j] = '\0';
			while (line[ms->l_idx + 1] == ' ')
				ms->l_idx++;
			if (line[ms->l_idx + 1] != '\0')
			{
				j = 0;
				k++;
			}
		}
		ms->l_idx++;
	}
	ms->args[k][j] = '\0';
	ms->args[k + 1] = '\0';
	return (0);
}
