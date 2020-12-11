#include "minishell.h"

void	ft_ms_echo(t_stock_str ms)
{
	int	hwyu;

	hwyu = 0;
	printf("\n-------------echo----------------\n");
	while (ms.args[hwyu])
	{
		hwyu++;
		if (ms.args[hwyu])
			ft_putstr_fd(ms.args[hwyu], 1);
		write(1, " ", 1);//NULL 일 경우에도 space가 들어가서 이친구가 조건문안에 들어가야할거같음
	}
	printf("\n-------------echo----------------\n");
}
