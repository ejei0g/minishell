#include "minishell.h"

void	err_invalid(t_stock_str *ms, int i)
{
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(ms->args[0], 1);
	ft_putstr_fd(": '", 1);
	ft_putstr_fd(ms->args[i], 1);
	ft_putstr_fd("': not a valid identifier", 1);
	ms->err = 1;
}

char	*err_path_dir(void)
{
	ft_putstr_fd(strerror(errno), 1);
	return (NULL);
}
