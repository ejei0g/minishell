#include "minishell.h"

void	rdir_fd_dup(t_stock_str *ms, int rdir_flag)
{
	int	fd = 0;

	if (rdir_flag == 1)
		fd = open(ms->file_name, O_WRONLY | O_CREAT | O_APPEND);
	else if (rdir_flag == 2)
		fd = open(ms->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (rdir_flag == 3)
		fd = open(ms->file_name, O_RDONLY);
	if (rdir_flag == 3)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
}

int		rdir_flag_setting(t_stock_str *ms, char *line)
{
	if (line[ms->l_idx] == '>' && line[ms->l_idx + 1] == '>')
	{
		ms->l_idx = ms->l_idx + 2;
		return (1);
	}
	else if (line[ms->l_idx] == '>')
	{
		ms->l_idx = ms->l_idx + 1;
		return (2);
	}
	else if (line[ms->l_idx] == '<')
	{
		ms->l_idx = ms->l_idx + 1;
		return (3);
	}
	return (0);
}

void	redirect_parsing(t_stock_str *ms, char *line)
{
	int	i = 0;
	int	rdir_flag;
	char	filename[100];
	int	cp_l_idx;

	i = 0;
	cp_l_idx = 0;
	rdir_flag = rdir_flag_setting(ms, line);
	while (line[ms->l_idx] == ' ' && line[ms->l_idx] != '\0')
		ms->l_idx++;
	cp_l_idx = ms->l_idx;
	while (line[ms->l_idx] != ' ' && line[ms->l_idx] != '\0')
		filename[i++] = line[ms->l_idx++];
	filename[i] = '\0';
	ms->file_name = ft_strdup(filename);
	if (ft_strncmp(ms->args[0], "echo", 4) == 0)
		return ;
	rdir_fd_dup(ms, rdir_flag);
	if (rdir_flag == 3)
		ms->l_idx = cp_l_idx;
	ms->l_idx--;
}
