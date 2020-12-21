#include "minishell.h"

int		rdir_fd_dup(t_stock_str *ms, int rdir_flag)
{
	int	fd;

	fd = 0;
	if (rdir_flag == 1)
		fd = open(ms->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (rdir_flag == 2)
		fd = open(ms->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (rdir_flag == 3)
	{
		if ((fd = open(ms->file_name, O_RDONLY)) < 0)
		{
			ft_putstr_fd("bash: ", 1);
			ft_putstr_fd(ms->file_name, 1);
			ft_putstr_fd(": No such file or directory\n", 1);
			ms->file_name[0] = '<';
			ms->err = 1;
			dup2(fd, STDIN_FILENO);
			return (-1);
		}
	}
	if (rdir_flag == 3)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	return (0);
}

int		rdir_flag_setting(t_stock_str *ms, char *line)
{
	if (line[ms->l_idx] == '>' && line[ms->l_idx + 1] == '>')
	{
		ms->l_idx = ms->l_idx + 2;
		while(line[ms->l_idx] == ' ')
			ms->l_idx++;
		return (1);
	}
	else if (line[ms->l_idx] == '>')
	{
		ms->l_idx = ms->l_idx + 1;
		while(line[ms->l_idx] == ' ')
			ms->l_idx++;
		return (2);
	}
	else if (line[ms->l_idx] == '<')
	{
		ms->l_idx = ms->l_idx + 1;
		while(line[ms->l_idx] == ' ')
			ms->l_idx++;
		return (3);
	}
	return (0);
}

int		redirect_parsing(t_stock_str *ms, char *line)
{
	int		i;
	int		rdir_flag;
	char	filename[100];

	i = 0;
	rdir_flag = rdir_flag_setting(ms, line);
	while (line[ms->l_idx] != ' ' && line[ms->l_idx] != '\0')
		filename[i++] = line[ms->l_idx++];
	filename[i] = '\0';
	printf("file = %s\n", filename);
	free(ms->file_name);
	ms->file_name = ft_strdup(filename);
	if (ms->file_name[0] == '>' || ms->file_name[0] == '<')
	{
		ft_putstr_fd("bash: syntax error near unexpected token \'", 1);
		write(1, &ms->file_name[0], 1);
		ft_putstr_fd("\'\n", 1);
		ms->err = 2;
		return (-1);
	}
	if (rdir_fd_dup(ms, rdir_flag) == -1)
		return (-1);
	ms->l_idx--;
	return (0);
}
