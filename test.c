#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#define MAX_BUF 1024
#define READ 0
#define WRITE 1

//int pipe(int fd[2]);
//return 0 or -1
//fd[0] 은 읽기를 위해 준비, fd[1]은 쓰기를 위해 준비.

int main()
{
	/*
        int fd[2];
        pid_t pid;
        char buf[MAX_BUF];

	printf("fd : %d, %d\n", fd[0], fd[1]);

        if(pipe(fd) < 0){
                printf("pipe error\n");
                exit(1);
        }
	printf("fd : %d, %d\n", fd[0], fd[1]);
        if((pid=fork())<0){
                printf("fork error\n");
                exit(1);
        }

        printf("\n");
        if(pid>0){ //parent process
		printf("parent fd : %d, %d\n", fd[0], fd[1]);

		dup2(1,3);
		env [fd1]
                close(fd[READ]);//3
		**buf
		abc = d;
		a = c;
                strcpy(buf,"message from parent\n");
                write(fd[WRITE],buf,strlen(buf));//4
        }else{  //child process
                close(fd[WRITE]);//4
		**buf
		buf | 
                read(fd[READ],buf,MAX_BUF);//3
                printf("child got message : %s\n",buf);
        }
	printf("fd : %d, %d\n", fd[0], fd[1]);
	*/
        int fd1, ret;
        char message[32]={"STDERR from fd1\n"};

        //그림 1번
        fd1=open("text.txt",O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
        if(fd1<0){
                printf("file open error\n");
                exit(0);
        }
        //표준 입출력으로 print됨
        printf("file open\n");

        //fd1의 파일 디스크립터가 명시한 STDOUT_FILENO의 파일 디스크립터로
        //복제됨,
        //그림 2번
        ret=dup2(fd1,STDOUT_FILENO);

	
        //fd1으로 출력됨
        printf("fd1 :%d, ret:%d\n",fd1,ret);

        //STDERR_FILENO 디스크립터가 명시된 fd1으로 복제됨
        //그림 3번
        ret=dup2(STDERR_FILENO,fd1);

        //fd1은 에러로 출력됨
        write(fd1,message,strlen(message));

        //stdout이 file로 써짐
        printf("printf를 썼지만 파일에 기록됨 \n");

        close(fd1);

}
