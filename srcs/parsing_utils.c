#include "minishell.h"

void	args_free(t_stock_str *ms)
{
	int i = 0;

	while (ms->args[i])
	{
		free(ms->args[i]);
		i++;
	}
	free(ms->args);
}
