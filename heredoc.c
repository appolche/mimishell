#include "minishell.h"


void	here_doc_child(int pipe_fd[2], char *limiter)
{
	char	*line;

	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(1);
		if (ft_strcmp(line, limiter) == 0)
		{
			// free(limiter);
			free(line);
			exit(0);
		}
		write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
		free(line);
	}
}

int	here_doc_mode(char *limiter)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		show_error("Error: Pipe\n");
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	if (pid == 0)
		here_doc_child(pipe_fd, limiter);
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
	}
	return (pipe_fd[0]);
		// pipe_parent_proc(pipe_fd, pid);
		
}