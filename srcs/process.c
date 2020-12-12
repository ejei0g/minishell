#include "minishell.h"

char	*make_apsolute_path(char const *s1, char const *s2)
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

//full path malloc
void	find_file_name(char *path)
{
	DIR		*dp;
	struct dirent	*entry;
	struct stat	buf;
	char	*full_path;

	if ((dp = opendir(path)) == NULL)
	{
		ft_putstr_fd(strerror(errno), 1);
		return ;
	}
	while ((entry = readdir(dp)) != NULL)
	{
		full_path = make_apsolute_path(path, entry->d_name);
		lstat(full_path, &buf);
		//printf("%d ", buf.st_mode);
		//if (S_ISDIR(buf.st_mode))
		if (S_ISREG(buf.st_mode))
		{
			ft_putstr_fd(entry->d_name, 1);
			ft_putstr_fd(" ", 1);
		}
		//ft_putstr_fd(full_path, 1);
		free(full_path);
	}
	closedir(dp);
	return ;
}

void	print_path(t_env_list **env)
{
	t_env_list *path;
	char	**paths;

	path = find_env_key(env, "PATH");
	printf("%s\n", path->data + 5);
	paths = ft_split(path->data + 5, ':');


	//dir 열고
	//정보 읽고
	// dir 닫고
	int i;
	i = 0;
	while (paths[i])
	{
		printf("%s%s%s\n", BLUE, paths[i], ORIGIN);
		find_file_name(paths[i]);
		i++;
	}
	//paths free;
	free_envp_arr(paths);
}

void	ft_ms_execve(t_stock_str ms, char *s, t_env_list *env)
{
	int	pid;
	t_env_list	*tmp;

	tmp = env;
	printf("%s\n", "start fork\n");
	pid = fork();
	printf("%s\n", tmp->data);
	if (pid == 0)
	{
		printf("i'm a child\n");
		execve(s, ms.args, 0);
	}
	else
	{
		printf("i'm a parent\n");
		//wait();
	}
}

void	ms_proc(t_stock_str ms, t_env_list **env)
{
	if (ft_strncmp(ms.args[0], ECHO, 4) == 0)
		ft_ms_echo(ms);
	else if (ft_strncmp(ms.args[0], CD, 2) == 0)
		ft_ms_cd(ms);
	else if (ft_strncmp(ms.args[0], PWD, 3) == 0)
		ft_ms_pwd();
	else if (ft_strncmp(ms.args[0], EXPORT, 6) == 0)
		ft_ms_export(ms, env);
	else if (ft_strncmp(ms.args[0], UNSET, 5) == 0)
		ft_ms_unset(ms, env);
	else if (ft_strncmp(ms.args[0], ENV, 3) == 0)
		ft_ms_env(*env);
	else if (ft_strncmp(ms.args[0], EXIT, 4) == 0)
		ft_ms_exit(env);
	//else
	//	ft_ms_execve(ms, ms.args[0], *env);
	return ;
}
