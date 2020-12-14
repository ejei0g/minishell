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

int	is_cmd(char *s1, char *s2)
{
	int	count;

	count = 0;
	if (ft_strlen(s1) > ft_strlen(s2))
		count = ft_strlen(s1);
	else
		count = ft_strlen(s2);
	if (ft_strncmp(s1, s2, count) == 0)
		return (1);
	return (0);
}

//full path malloc
char	*find_file_name(char *path, char *file_name)
{
	DIR		*dp;
	struct dirent	*entry;
	struct stat	buf;
	char	*full_path;

	if ((dp = opendir(path)) == NULL)
		return (err_path_dir());
	while ((entry = readdir(dp)) != NULL)
	{
		if (is_cmd(file_name, entry->d_name))
		{
			full_path = make_full_path(path, entry->d_name);
			lstat(full_path, &buf);
			if (S_ISREG(buf.st_mode))
			{
				closedir(dp);
				return (full_path);
			}
			free(full_path);
		}
	}
	closedir(dp);
	return (0);
}

void	print_path(t_env_list **env)
{
	t_env_list *path;
	char	**paths;

	path = find_env_key(env, "PATH");
	printf("%s\n", path->data + 5);
	paths = ft_split(path->data + 5, ':');

	int i;
	i = 0;
	while (paths[i])
	{
		printf("%s%s%s\n", BLUE, paths[i], ORIGIN);
		i++;
	}
	//paths free;
	free_envp_arr(paths);
}

char	*chk_file_in_path(t_stock_str ms, t_env_list **env)
{
	char	*file;
	t_env_list *path;
	char	**paths;
	int	i;

	i = 0;
	path = find_env_key(env, "PATH");
	paths = ft_split(path->data + 5, ':');
	while (paths[i])
	{
		if ((file = find_file_name(paths[i], ms.args[0])) != NULL)
		{
			free_envp_arr(paths);
			return (file);
		}
		i++;
	}
	free_envp_arr(paths);
	return (NULL);
}

void	ft_ms_execve(t_stock_str ms, char *file)
{
	pid_t	pid;
	int	status;

	pid = fork();
	if (pid == 0)
		execve(file, ms.args, 0);
	else
	{
		waitpid(-1, &status, 0);
		printf("parent live?\n");
	}
}

void	ft_ms_else(t_stock_str ms, t_env_list **env)
{
	char	*file;

	if ((file = chk_file_in_path(ms, env)) != NULL)
	{
		ft_ms_execve(ms, file);
		free(file);
	}
	else
	{
		ft_putstr_fd(ms.args[0], 1);
		ft_putstr_fd(": command not found\n", 1);
		return ;
	}
}

/**
 *  1. 명령어 예외가 들어왔을 때
 *  2. file_name vs PATH file
 *  3. 1. PATH split
 *  	2. 전체탐색.
 *  	3.-1 없으면 종료
 *  	3-2 있으면 전체경로 전달하고 execve
 *  4. 조건이 맞으면 fork로 execve 실행
 *
 */

void	ms_proc(t_stock_str ms, t_env_list **env)
{
	if (is_cmd(ms.args[0], ECHO))
		ft_ms_echo(ms);
	else if (is_cmd(ms.args[0], CD))
		ft_ms_cd(ms);
	else if (is_cmd(ms.args[0], PWD))
		ft_ms_pwd();
	else if (is_cmd(ms.args[0], EXPORT))
		ft_ms_export(ms, env);
	else if (is_cmd(ms.args[0], UNSET))
		ft_ms_unset(ms, env);
	else if (is_cmd(ms.args[0], ENV))
		ft_ms_env(*env);
	else if (is_cmd(ms.args[0], EXIT))
		ft_ms_exit(env);
	else
		ft_ms_else(ms, env);
	return ;
}
