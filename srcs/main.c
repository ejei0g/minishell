#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "../libft/libft/libft.h"

/*
 * echo		[]
 * cd		[o]
 * pwd		[o]
 * export	[o]
 * unset	[]
 * env		[o]
 * exit		[o]
 *
 */

extern char **environ;

void	ft_pwd(void)
{
	char path[10000];

	getcwd(path, 10000);
	printf("%s\n", path);
}

void	ft_chdir(/*t_stock_str *st*/)
{
	//st->arg[0] = "..";
	char *s;

	s = "..";
	if (chdir(s) == -1)
	{
		printf("failed, change dir\n");//errno
	}
	else
	{
		printf("After Current directory\n");
	}
	//ft_pwd();
}

void	ft_execve(char **envp)
{
//	int fd_pipe[2];
	//char *data1[] = {"grep", "PATH", 0};
	char *data2[] = {"ls", "-al", 0};

	printf("envp = %s\n", envp[0]);
//	pid_t pid;
//
//	pipe(fd);

	int pid;
	pid = fork();
	if (pid == 0)
	{
		printf("child\n");
		execve("/bin/ls", data2, 0);
	}
	else
	{
		printf("parent\n");
	}
	//execve("/bin/grep", data1, 0);
//	else
//	{
//	printf("hi");
//	}
//	printf("exit");
}

void	ft_test()
{
	//char *s = "vi main.c";
	//char *data_argv[] = {"vi", "main.c", 0};
	//env | grep 
	//0. 'vim'
	//1. path 경로 검색 => usr/ /bin /sbin /usr/local
	//2. opendir(/usr/) = sdfk. sdf.s df. sdf. s.f**char, a
	//2. arg[0] 이랑 매칭 = 있으면 실행 없으면 다른 것
	//	=> execve('asdfasf', args, 0);
	//3. 없으면 에러쳐리.
	// ms.cmd, data= ma.args
//	execve("/usr/bin/vi", data, 0 );
}

//env
void	ft_env(char **envp)
{
	int i;
	i = 0;
	//sorting.
	///sorting 없으면 envp
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

//TODO: 만약 인자가 추가로 들어올 경우 기존envp에 추가해줘야하므로 다른 처리가 필요함.
void	ft_export(char **envp)
{
	int	i;
	int	max_index;
	char	*tmp;

	i = 0;
	max_index = 0;
	while (envp[max_index])
	{
		max_index++;
	}
	printf("max index of envp : %d\n", max_index);
	while (i < max_index - 1)
	{//TODO: free할 때 메모리 누수 처리가 잘 되었는지 확인 필요.
		if (ft_strncmp(envp[i], envp[i + 1], ft_strlen(envp[i])) > 0)
		{
			//앞에 것과 뒤에것을 비교해서 만약 앞에가 크면 둘이 체인지.
			tmp = ft_strdup(envp[i]);
			free(envp[i]);
			envp[i] = envp[i + 1];
			envp[i + 1] = tmp;
			i = 0;
			//envp[i] = ft_strdup(envp[i + 1]);
		}
		i++;
	}
	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

#define ENVS_SIZE 100000
char	**ft_envdup(char **envp)
{
	char **cp_envp;
	int	i;

	i = 0;
	cp_envp = (char **)malloc(sizeof(char *) * ENVS_SIZE);
	if (cp_envp == NULL)
		return (NULL);
	while (envp[i])
	{
		cp_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	cp_envp[i] = '\0';
	return (cp_envp);
}

char	*ft_return_value(char **envp, const char *key)
{
	char *ret;
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
		{
			ret = ft_strdup(envp[i]);
			break;
		}
		i++;
	}
	return (ret);
}

//extern char **environ == *envp[]
int main(int argc, char *argv[], char *envp[])
{
	char	**cp_envp;//환경변수 복사(unset, export로 변수추가하고 기존거에 영향안주기 위해(포크했을 때))
	char	*line;
	int	i;
	//t_stock_str ms;
	printf("argc : %d, argv[0] : %s\n", argc, argv[0]);
//	init,초기화할때 환경변수 복사하고 그거 사용하기 
	cp_envp = ft_envdup(envp);

	printf("%s$", ft_return_value(cp_envp, "USER"));


	i = 0;
	while ((i = get_next_line(0, &line)) > 0)
	{
//		parsing_line(&st, line);
		//1. line
		//2. parsing
		//3. process
		//3-1. evc.. expor.. exit
		//3-1-1 exit
		if (i == 0)
		{
			exit(0);
			free(line);
		}
		//parsing(&ms, line);
		if (ft_strncmp(line, "exit", 4) == 0)
			break ;
		else if (ft_strncmp(line, "pwd", 3) == 0)
			ft_pwd();
		else if (ft_strncmp(line, "cd", 2) == 0)
			ft_chdir();
		else if (ft_strncmp(line, "ls", 2) == 0)
			ft_execve(envp);
		else if (ft_strncmp(line, "export", 6) == 0)
			ft_export(cp_envp);
		else if (ft_strncmp(line, "env", 3) == 0)
			ft_env(cp_envp);
		else if (ft_strncmp(line, "test", 4) == 0)
			ft_test();
	}
	return (0);
}
