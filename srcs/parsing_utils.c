#include "minishell.h"

void	str_init(t_stock_str *ms)
{
	ms->w = 0;
	ms->h = 0;
	ms->p_flag = 0;
	ms->sc_flag = 0;
	ms->sq_flag = 0;
	ms->dq_flag = 0;
	ms->null_flag = 0;
}

void	args_free(t_stock_str *ms)
{
	int i;

	i = 0;
	free(ms->last_args);
	while (ms->args[i])
	{
		free(ms->args[i]);
		i++;
	}
	free(ms->args);
}
