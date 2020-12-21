#include "minishell.h"

void	ft_ms_echo(t_stock_str *ms)
{
	int	hwyu;

	hwyu = 0;
	while (ms->args[hwyu])
	{
		hwyu++;
		if (ms->args[hwyu])
			ft_putstr_fd(ms->args[hwyu], 1);
		if (ms->args[hwyu] != NULL)
		{
			if (ms->args[hwyu + 1] != NULL)
				write(1, " ", 1);
		}
	}
	ms->err = 0;
	if (ms->null_flag == -1 || ms->null_flag == 0)
		write(1, "\n", 1);
}
