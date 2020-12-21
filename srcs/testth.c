parsing
if (pipe)
{
	ft_pipe()
}


ft_pipe(){
	pid_t a;
	pid_t b;
	int	fd[2];


	if (pipe(fd) == -1)
	a = fork();
	if a<0
	if a == 0
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve();
	}
	if b == 0 
	{
		dup2(fd[0], STDIN_FILENO);
		free(arg);
		ma
	}
	waitpid(b, 0, 0);
	dajsiojsoi


}
