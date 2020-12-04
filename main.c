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
void	ft_execve()
{
	int fd[2];
	char *data1[] = {"ls", 0};
	pid_t pid;

	pipe(fd);

	pid = fork();
	if (pid == 0)
	{
		execve("/bin/ls", data1, 0);
	}
	else
	{
	printf("hi");
	}
	printf("exit");
}
int main(int argc, char *argv[], char *envp[])
{
	char *line;
	int i;
	t_stock_str st;


	line = "cd .. ; ls";
//	write(1, "$ ", 11);
	while ((i = get_next_line(0, &line)) > 0)
	{
		//count = kk2;

		st->cmd = cd
			arg = ..
			st->flag = 0;
		pipe_flag = 1;
		while (flag == 1)
		{
		parsing_line(&st, &line);
		line = %s = " ls";
			//			; 
//		parsing_line(&st, line);
		//1. line
	//	printf("bash:@%s\n", line);
		//2. parsing.
		//3. process 
		//3-1. evc.. expor.. exit
		//3-1-1 exit
		//			exit();
		//
//		write(1, "Minishell$ ", 11);
		if (strncmp(line, "exit", 4) == 0)
			break ;
		else if (strncmp(line, "pwd", 3) == 0)
			ft_pwd();
		else if (strncmp(line, "cd", 2) == 0)
			ft_chdir();
		else if (strncmp(line, "ls", 2) == 0)
			ft_execve();
		free(st);
	}
		free(line);
	}
	printf("i = %d\n", i);
	return (0);
}
