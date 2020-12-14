#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#define STDIN_PIPE 0x1
#define STDOUT_PIPE 0x2
int main()
{
    int pipefd1[2], pipefd2[2];
    pipe(pipefd1);
    pipe(pipefd2);
    char *const argv[] = {"/bin/ls", NULL};
    char *const argv2[] = {"/usr/bin/wc", NULL};
    char *const argv3[] = {"/usr/bin/wc", NULL};
    char *const envp[] = {NULL};
    printf("STDOUT_FILENO = %d", STDOUT_FILENO);
    printf("STDOUT_FILENO = %d", STDIN_FILENO);
    pid_t pid = fork();
    if (pid > 0)
    {
        sleep(1);
    }
    else
    {
        close(pipefd1[0]);
        dup2(pipefd1[1], STDOUT_FILENO);
        close(pipefd1[1]);
        execve("/bin/ls", argv, envp);
    }
    // pipefd1[0] =담겨있다.
    pid_t pid2 = fork();
    if (pid2 > 0)
        sleep(1);
    else
    {
        close(pipefd1[1]);
        dup2(pipefd1[0], STDIN_FILENO);
        close(pipefd1[0]);
        //
        close(pipefd2[0]);
        dup2(pipefd2[1], STDOUT_FILENO);
        close(pipefd2[1]);
        execve("/usr/bin/wc", argv2, envp);
    }
    // fd2[0]에 담김 ls | wc;
    printf("hello\n");
    close(pipefd1[0]);
    close(pipefd1[1]);
    close(pipefd2[1]);
    dup2(pipefd2[0], STDIN_FILENO);
    close(pipefd2[0]);
    execve("/usr/bin/wc", argv2, envp);
    /*
    printf("tttthello\n");
    //int temp_pipefd[] = {pipefd1[0], pipefd2[1]}; //3, 6보냈어.
    //exec_command("/usr/bin/wc", temp_pipefd, STDIN_PIPE | STDOUT_PIPE);
    execve("/usr/bin/wc", argv3, envp);*/
/*
    dup2(pipefd2[0], STDOUT_FILENO);
    dup2(pipefd1[1], STDIN_FILENO);
    //dup2(pipefd2[0], STDIN_FILENO);
    printf("tttthello\n");
    execve("/usr/bin/wc", argv3, envp);
    close(pipefd1[1]); //close로 안닫으면 결과 출력안됨.
    close(pipefd2[0]);*/
    //close(pipefd1);
}
