#include "minishell.h"

int		dollor_argcv(t_stock_str *ms, char *line, int i)
{
	if (line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9')
	{
		while (line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9')
			i = i * 10 + line[ms->l_idx++] - 48;
		argv_parsing(ms, i);
		return (0);
	}
	else if (line[ms->l_idx] == '#')
	{
		ms->args[ms->h][ms->w++] = ms->argc + 48 - 1;
		ms->l_idx++;
		return (0);
	}
	else if (line[ms->l_idx] == '?')
	{
		free(ms->args[ms->h]);
		ms->args[ms->h] = ft_itoa(ms->err);
		ms->l_idx++;
		ms->w = ms->w + ft_strlen(ms->args[ms->h]);
		return (0);
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
		if (brace == 1)
			ms->l_idx++;
		ms->l_idx--;
		return (-1);
	}
	if (!((line[ms->l_idx] >= 'a' && line[ms->l_idx] <= 'z') ||
		(line[ms->l_idx] >= 'A' && line[ms->l_idx] <= 'Z') ||
		line[ms->l_idx] == '_'))
	{
		ms->args[ms->h][ms->w++] = '$';
		ms->l_idx--;
		return (-1);
	}
	return (brace);
}

void	dollor_parsing(t_stock_str *ms, char *line, t_env_list *head)
{
	int		brace;
	int		j;
	char	a[100];

	brace = 0;
	j = 0;
	ms->l_idx++;
	brace = dollor_parsing2(ms, line, brace);
	if (brace == -1)
		return ;
	while ((line[ms->l_idx] >= '0' && line[ms->l_idx] <= '9') ||
		(line[ms->l_idx] >= 'a' && line[ms->l_idx] <= 'z') ||
		(line[ms->l_idx] >= 'A' && line[ms->l_idx] <= 'Z') ||
		line[ms->l_idx] == '_')
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
