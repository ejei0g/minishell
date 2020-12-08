#inlcude "minishell.h"

int	flag_check(t_stock_str *ms, char c)
{
	if (c == '\'')
		ms.sq_flag == 1;
	else if (c == '\"')
		ms.dq_flag == 1;
	else if (c == ';')
		ms.sc_flag == 1;
	else if (c == '|')
		ms.p_flag == 1;
	else
		return (1);
	return (0);
}
void	str_init(t_stock_str *ms)
{
	int i;
	int j;

	i = 0;
	while (ms.args[i])
	{
		j = 0;
		while (ms.args[i][j])
		{
			ms.args[i][j] = '\0';
			j++;
		}
		i++;
	}
	ms.p_flag = 0;//pipe flag
	ms.sc_flag = 0;//semicolon flag
	ms.l_idx = 0; //line index
	ms.sq_flag = 0; // single quarter
	ms.dq_flag = 0; // double quarter
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
	while (line[ms->l_idx])
	{
		if (flag_check(ms, line[ms->l_idx]) == 0) // i - 1 부분 세그먼트오류조심
		{
			ms->l_idx++;
			continue ;
		}
		*ms->args[k][j] = line[ms->l_idx];
		ms->l_idx++;
		j++;
		if (line[ms->l_idx] == ' ')
		{
			k++;
			j = 0;
			while (line[ms->l_idx] != ' ')
				ms->l_idx++;
		}
	}
	return (0);
}