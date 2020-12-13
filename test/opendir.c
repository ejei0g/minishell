#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

//opendir, closedir, readdir
#include <sys/types.h>
#include <dirent.h>

//int lstat(const char *path, struct stat *buf);
#include <sys/stat.h>

#define RED	"\033[31m"

void	print_strerr()
{
	int i;

	i = 0;
	while (i < 150)
	{
		printf("%d, %s\n", i, strerror(i));
		i++;
	}
}

void	open_file()
{
	FILE *fp = NULL;
	char buffer[100];

	if ((fp = fopen("test.txt", "r")) == NULL)
	{
		write(1, strerror(errno), strlen(strerror(errno)));
		printf("%s\n", strerror(errno));
	}
	while (fgets(buffer, 100, fp) != NULL)
		printf("%s", buffer);
	fclose(fp);
}

//struct dirent *readdir(DIR *dp);
//struct dirent
//{
//	long	d_ino;
//	off_t	d_off;
//	unsigned short	d_reclen;
//	char	d_name[NAME_MAX+1];
//}

int	main(int argc, char **argv, char **envp)
{
	DIR *dp = NULL;
	struct dirent *entry = NULL;
	struct stat buf;

	//printf("%s\n",  strerror(127));
	print_strerr();

	// Q2? 경로와 현재위치가 다를경우 제대로된 파일/디렉토리 구분을 해주지 못함.
	if ((dp = opendir("/home/jaeylee/")) == NULL)
	{
		write(1, strerror(errno), strlen(strerror(errno)));
		return (-1);
	}
	// Q1? 왜 +같은 연산이 없는데 반복문이 돌수있는걸까?
	int i;
	while ((entry = readdir(dp)) != NULL)
	{
		/*
		lstat(entry->d_name, &buf);
		if (S_ISDIR(buf.st_mode))
			printf("DIR :%s\n", entry->d_name);
		else if (S_ISREG(buf.st_mode))
			printf("file:%s\n", entry->d_name);
		else
			printf("?\n");
			*/
		lstat(entry->d_name, &buf);
		i = S_ISREG(buf.st_mode);
		printf("file?:%d, %s\n", i, entry->d_name);
	}
	closedir(dp);
	return (0);
}
