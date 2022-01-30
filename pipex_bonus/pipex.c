#include "pipex.h"

void	parent_proc(int pipe_fd[2], int file_fd[2], pid_t pid)
{
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], 0) < 0)
		show_error("Error: Pipe_fd dup failed\n");
	close(pipe_fd[0]);
	waitpid(pid, NULL, 0);
}

void	child_proc(char *argv, char **envp, int pipe_fd[2], int file_fd[2])
{
	char	**cmd;

	close(pipe_fd[0]);
	if (dup2(pipe_fd[1], 1) < 0)
		show_error("Error: Pipe_fd dup failed\n");
	close(pipe_fd[1]);
	cmd = ft_split(argv, ' ');
	if (!cmd)
		show_error("Error: Cmd didn't split\n");
	ft_exec(cmd, envp);
}

void	cmd_proc(char *argv, char **envp, int file_fd[2])
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		show_error("Error: Pipe\n");
	pid = fork();
	if (pid == -1)
		show_error("Error: Fork\n");
	if (pid == 0)
		child_proc(argv, envp, pipe_fd, file_fd);
	else
		parent_proc(pipe_fd, file_fd, pid);
}

void	choose_mode(char **argv, int *file_fd, int *i)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		*i = 3;
		here_doc_mode(ft_strjoin(argv[2], "\n"), file_fd);
	}
	else
	{
		*i = 2;
		file_fd[0] = open(argv[1], O_RDONLY);
		if (file_fd[0] == -1)
			show_error("Error: Open first file failed\n");
		if (dup2(file_fd[0], 0) < 0)
			show_error("Error: File_fd dup failed\n");
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	file_fd[2];
	int	i;

	if (argc < 5)
	{
		show_error("Usage Error: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n");
		show_error("Usage Error: ./pipex here_doc LIMITER cmd cmd1 file\n");
	}
	file_fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (file_fd[1] == -1)
		show_error("Error: Open last file failed\n");
	choose_mode(argv, file_fd, &i);
	while (i < argc - 2)
		cmd_proc(argv[i++], envp, file_fd);
	if (dup2(file_fd[1], 1) < 0)
		show_error("Error: File_fd dup failed\n");
	ft_exec(ft_split(argv[argc - 2], ' '), envp);
	return (0);
}
