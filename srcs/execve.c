/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 21:26:56 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/22 18:43:06 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*make_full_path(char const *s1, char const *s2)
{
	char			*joined_str;
	unsigned int	jstr_len;

	if (!s1 || !s2)
		return (NULL);
	jstr_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined_str = (char *)malloc(sizeof(char) * (jstr_len + 1));
	if (joined_str == NULL)
		return (NULL);
	while (*s1)
		*joined_str++ = *s1++;
	*joined_str++ = '/';
	while (*s2)
		*joined_str++ = *s2++;
	*joined_str = '\0';
	return (joined_str - jstr_len);
}

char	*find_file_name(char *path, char *file_name)
{
	DIR				*dp;
	struct dirent	*entry;
	struct stat		buf;
	char			*full_path;

	if ((dp = opendir(path)) == NULL)
		return (err_path_dir());
	while ((entry = readdir(dp)) != NULL)
	{
		full_path = make_full_path(path, entry->d_name);
		if (is_cmd(full_path, file_name))
			return (full_path);
		if (is_cmd(file_name, entry->d_name))
		{
			lstat(full_path, &buf);
			if (S_ISREG(buf.st_mode))
			{
				closedir(dp);
				return (full_path);
			}
		}
		free(full_path);
	}
	closedir(dp);
	return (0);
}

char	*chk_file_in_path(t_stock_str *ms, t_env_list **env)
{
	char		*file;
	t_env_list	*path;
	char		**paths;
	int			i;

	i = 0;
	if ((path = find_env_key(env, "PATH")) == NULL)
		return (NULL);
	paths = ft_split(path->data + 5, ':');
	while (paths[i])
	{
		if ((file = find_file_name(paths[i], ms->args[0])) != NULL)
		{
			free_envp_arr(paths);
			return (file);
		}
		i++;
	}
	free_envp_arr(paths);
	return (NULL);
}

void	ft_ms_execve(t_stock_str *ms, char *file)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
		execve(file, ms->args, 0);
	else
	{
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		ms->err = status;
	}
}

void	ft_ms_else(t_stock_str *ms, t_env_list **env)
{
	char	*file;

	if ((file = chk_file_in_path(ms, env)) != NULL)
	{
		ft_ms_execve(ms, file);
		free(file);
	}
	else
	{
		if (ms->args[0][0] == '/')
		{
			ft_putstr_fd("bash: ", 1);
			ft_putstr_fd(ms->args[0], 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
		else
		{
			ft_putstr_fd(ms->args[0], 1);
			ft_putstr_fd(": command not found\n", 1);
		}
		ms->err = 127;
		return ;
	}
}
