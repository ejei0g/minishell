#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

int	main()
{
	int pid1;
	int fd;
	char *args[] = {"ls", "-al", 0};
	int	fd_copy;

	fd_copy = fd;
	fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("oiasjdoasj\n");
	dup2(fd, STDOUT_FILENO);
	printf("oiasjdoasj\n");
	dup2(fd_copy, STDOUT_FILENO);
	//&fd = fd_copy;
	printf("hello\n");
	/*
	pid1 = fork();
	printf("hello\n");
	printf("fd = %d\n", fd);
	if (pid1 == 0)
	{
		fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("fd = %d\n", fd);
		fd_copy = fd;
	//O_CREAT를 없애고, O_APPEND를 해주면 '>>' redirection임
		dup2(fd, STDOUT_FILENO);
		execve("/bin/ls", args, 0);
		printf("hello\n");
		//fd = fd_copy;
		//close(fd);
	}*/
	//sleep(1);
	//printf("fd = %d\n", fd);
	//waitpid(pid1, NULL, 0);
}
