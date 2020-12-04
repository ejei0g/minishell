#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
void	ft_putendl_fd(char *s, int fd)
{
	int	i;
	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}
int		ft_pwd(void)
{
	char	cwd[1000];
	if (getcwd(cwd, 1000))
	{
		ft_putendl_fd(cwd, 1);
		return (1);
	}
	else
		return (0);
}
int main(int argc, char *argv[], char *envp[])
{
//	char a[3];
//	read(0, a, sizeof(a));
//	a[2] = '\0';
//	printf("a = %s\n", a);
//	execlp(a, a, NULL);
	ft_pwd();
/*	int i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'W' && envp[i][2] == 'D')
		{
			printf("envp = %s\n", envp[i]);
			break ;
		}
		i++;
	}*/
	return (0);
}
