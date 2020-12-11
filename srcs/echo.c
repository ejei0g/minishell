#include "minishell.h"

void	ft_ms_echo(t_stock_str ms)
{
	int hwyu = 0;
	printf("\n-------------echo----------------\n");
	while (ms.args[hwyu])
	{
		hwyu++;
		if (ms.args[hwyu])
			ft_putstr_fd(ms.args[hwyu], 1);
		write(1, " ", 1);
	}
	printf("\n-------------echo----------------\n");
}
