#include "minishell.h"

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

void	args_free(t_stock_str *ms)
{
	int i = 0;

	free(ms->last_args);
	while (ms->args[i])
	{
		free(ms->args[i]);
		i++;
	}
	free(ms->args);
}
