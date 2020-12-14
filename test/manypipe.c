#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define STDIN_PIPE 0x1
#define STDOUT_PIPE 0x2

void	exec_command(char *command, int pipefd[2], int flags)
{
	pid_t cpid = fork();
	if (cpid > 0)
		return ;
	else if (cpid < 0)
		perror("fork");

	if (flags & STDIN_PIPE)
	{
		printf("in\n");
		if (dup2(pipefd[0], STDIN_FILENO) < 0) //인풋이 연결된 파이프의 read로 바뀜
			perror("dup2");

	}

	if (flags & STDOUT_PIPE)
	{
		printf("out\n");
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)//출력이 연결된 파이프의 wirte로 바뀜
			perror("dup2");

	}

	//왜 닫을까 ..?
	close(pipefd[0]);
	close(pipefd[1]);
	//일단 커맨드실행할 때, 인풋이나 아웃풋 하나만 연결된 파이프랑 바꿔주고 파이프닫고.

	char *const argv[] = {command, NULL};
	char *const envp[] = {NULL};
	execve(command, argv, envp);
	perror("execv");
}

int	main()
{ //파이프를 두개 만들고 각각의 역할을 구분해줌.
	//1. close를 해도 fd의 값은 변하지 않는다.
	//2. pipe fd0 : read역할, fd1은 write의 역할
	//
	int	pipefd1[2], pipefd2[2];
	//첫번째 파이프와 두번째파이프 열고
	pipe(pipefd1);
	pipe(pipefd2);

	//첫번째 파이프를 출력파이프로 전달해줫어.
	exec_command("/bin/ls", pipefd1, STDOUT_PIPE);
	close(pipefd1[1]); //write를 닫고
	exec_command("/usr/bin/wc", pipefd2, STDIN_PIPE);
	close(pipefd2[0]); //read를 닫고

	printf("%d??\n", STDIN_PIPE | STDOUT_PIPE);
	int temp_pipefd[] = {pipefd1[0], pipefd2[1]}; //3, 6보냈어.
	//이 뜻은 뭐냐. 3으로 read하고 6으로 write한다.
	exec_command("/usr/bin/wc", temp_pipefd, STDIN_PIPE | STDOUT_PIPE);

	close(pipefd1[0]); //close로 안닫으면 결과 출력안됨.
	close(pipefd2[1]);


	printf("%d, %d, %d, %d\n", pipefd1[0], pipefd1[1], pipefd2[0], pipefd2[1]);
	printf("%d, %d\n", temp_pipefd[0], temp_pipefd[1]);
	int wstatus;
	while (wait(&wstatus) > 0);

	printf("%d, %d, %d, %d\n", pipefd1[0], pipefd1[1], pipefd2[0], pipefd2[1]);
	return (0);
}
