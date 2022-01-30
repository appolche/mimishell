#include "pipex.h"

void	here_doc_child(int pipe_fd[2], char *limiter)
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		line = gnl_stdin(0);
		if (!line)
			exit(1);
		if (ft_strcmp(line, limiter) == 0)
		{
			free(limiter);
			free(line);
			exit(0);
		}
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
}

void	here_doc_mode(char *limiter, int file_fd[2])
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		show_error("Error: Pipe\n");
	pid = fork();
	if (pid == -1)
		show_error("Error: Fork\n");
	if (pid == 0)
		here_doc_child(pipe_fd, limiter);
	else
		parent_proc(pipe_fd, file_fd, pid);
}
