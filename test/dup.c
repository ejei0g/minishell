#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int fd1, fd2;
	char message2[32] = "message via fd2\n";
	char message1[32] = "message via fd1\n";
	printf("fd1 : %d, fd2:%d\n", fd1, fd2);


	fd1 = open("file_1", O_RDWR | O_CREAT, S_IRUSR|S_IWUSR);
	if (fd1 <0)
	{
		printf("error\n");
		exit(0);
	}
	fd2 = dup(fd1); //전달받은 파일디스크립터를 복제하고 반환

	write(fd2, message2, strlen(message2));
	write(fd1, message1, strlen(message1));
	printf("fd1 : %d, fd2:%d\n", fd1, fd2);
	close(fd1);
	close(fd2);
}
