#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int fd1, fd2;
	char message1[32] = "message via fd1\n";
	int ret;


	fd1 = open("file_dup2", O_RDWR | O_CREAT, S_IRUSR|S_IWUSR);
	if (fd1 <0)
	{
		printf("error\n");
		exit(0);
	}
	//dup2 (int fd, int fd2); fd2를 

	/**
	 *  0 : STDIN_FILENO
	 *  1 : STDOUT_FILENO
	 *  2 : STDERR_FILENO
	 */
	//표준입출력 출력
	printf("hello by stdoutput\n");
	printf("ret : %d, fd1 : %d, out: %d\n", ret, fd1, STDOUT_FILENO);
	//fd1은 열려있는 파일이고, 파일의 fd를 1로 복제
	//그림2
	int out;

	out = dup(1);

	ret = dup2(fd1, STDOUT_FILENO); //뒤에가 앞에를 가리키게.
	printf("ret : %d, fd1 : %d, out: %d\n", ret, fd1, STDOUT_FILENO);

	//STDERR_FILENOㅐ
	//그림3

	ret = dup2(STDERR_FILENO, fd1);
	char *message = "error!!!!\n";
	write(fd1, message, strlen(message));
	printf("원상복구전.\n");
	write(1, message, strlen(message));



	//원상복구
	ret = dup2(out, STDOUT_FILENO);
	printf("ret : %d, fd1 : %d, out: %d\n", ret, fd1, STDOUT_FILENO);
	printf("return\n");

	//fd2 = dup(fd1); //전달받은 파일디스크립터를 복제하고 반환 둘다 똑같은 걸 가리킨 번호는 다르지만.

	close(fd1);
	close(fd2);
}
