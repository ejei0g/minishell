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

extern char **environ;

typedef struct s_stock_str {
	char *cmd;
	char **arg;
	char **env; //**env;

}	t_stock_str;

void	ft_pwd(void)
{
	char path[1000];

	getcwd(path, 1000);
	printf("%s\n", path);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	temp_s1;
	unsigned char	temp_s2;

	i = 0;
	while (i < n && (*(s1 + i) || *(s2 + i)))
	{
		if (*(s1 + i) == *(s2 + i))
			i++;
		else
		{
			temp_s1 = *(s1 + i);
			temp_s2 = *(s2 + i);
			return (temp_s1 - temp_s2);
		}
	}
	return (0);
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
	ft_pwd();
}

void	ft_execve(char **envp)
{
	//int fd_pipe[2];
	char *data1[] = {"grep", "PATH", 0};
	printf("envp = %s\n", envp[0]);
//	pid_t pid;
//
//	pipe(fd);

//	pid = fork();
//	if (pid == 0)
//	{
		execve("/bin/grep", data1, 0);
//	}
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

void	ft_export(char **envp)
{
	int i;
	i = 0;
	//sorting.
	///sorting 없으면 envp
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

int main(int argc, char *argv[], char *envp[])
{
	char **cp_envp;
	char *line;
	int i;
	printf("argc : %d, argv[0] : %s\n", argc, argv[0]);
	//t_stock_str ms;

	cp_envp = ft_envdup(envp);
	i = 0;
	while (cp_envp[i])
	{
		if (strncmp(cp_envp[i], "PATH", 4) == 0)
			printf("%s\n", cp_envp[i]);
		i++;
	}
	printf("hello!\n");
	/*
	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	environ[i] = "hello world!";
	environ[i][12] = '\0';
	environ[i + 1] = '\0';
	i = 0;
	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	printf("%s\n", environ[i]);
//	init,초기화할때 환경변수 복사하고 그거 사용하기 
	*/
	i = 0;
	while ((i = get_next_line(0, &line)) > 0)
	{
//		parsing_line(&st, line);
		//1. line
		//2. parsing
		//3. process
		//3-1. evc.. expor.. exit
		//3-1-1 exit

		//parsing(&ms, line);
		if (strncmp(line, "exit", 4) == 0)
			break ;
		else if (strncmp(line, "pwd", 3) == 0)
			ft_pwd();
		else if (strncmp(line, "cd", 2) == 0)
			ft_chdir();
		else if (strncmp(line, "ls", 2) == 0)
			ft_execve(envp);
		else if (strncmp(line, "export", 6) == 0)
			ft_export(envp);
		else if (strncmp(line, "test", 4) == 0)
			ft_test();
	}
	return (0);
}
