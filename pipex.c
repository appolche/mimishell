#include "minishell.h"

void	show_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}

void	absolute_path_exec(char **cmd, char **envp)
{
	if (!access(cmd[0], X_OK))
	{
		if (execve(cmd[0], cmd, envp) == -1)
			malloc_free(cmd);
		show_error("Error: Cmd execution failed\n");
	}
	malloc_free(cmd);
	show_error("Error: Path not found\n");
}

static void	path_search(char **path, char **cmd, char **envp)
{
	char	*final_path;
	char	*tmp;
	int		j;

	j = 0;
	while (path[++j])
	{
		tmp = ft_strjoin(path[j], "/");
		final_path = ft_strjoin(tmp, cmd[0]);
		free (tmp);
		if (!access(final_path, X_OK))
		{
			if (execve(final_path, cmd, envp) == -1)
			{
				malloc_free(path);
				malloc_free(cmd);
				if (final_path)
					free(final_path);
				show_error("Error: Cmd execution failed\n");
			}
		}
		if (final_path)
			free(final_path);
	}
	malloc_free(path);
}

static void	ft_exec(char **cmd, char **envp)
{
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
		absolute_path_exec(cmd, envp);
	while (envp[i])
	{
		if ((ft_strnstr(envp[i], "PATH=", 5)))
		{
			path = ft_split(envp[i], ':');
			break ;
		}
		i++;
	}
	if (path)
		path_search(path, cmd, envp);
	if (cmd)
		malloc_free(cmd);
	show_error("Error: Path not found\n");
}

void	child_proc(char **argv, char **envp, int pipe_fd[2], int file_fd[2])
{
	char	**cmd;

	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	dup2(file_fd[0], 0);
	cmd = ft_split(*argv, ' ');
	ft_exec(cmd, envp);
}

void	parent_proc(char **argv, char **envp, int pipe_fd[2], int file_fd[2])
{
	char	**cmd;

	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	dup2(file_fd[1], 1);
	cmd = ft_split(*argv, ' ');
	ft_exec(cmd, envp);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	int		file_fd[2];
// 	int		pipe_fd[2];
// 	pid_t	pid;

// 	if (argc != 5)
// 		show_error("Usage Error: ./pipex file1 cmd1 cmd2 file2\n");
// 	if (pipe(pipe_fd) == -1)
// 		show_error("Error: Pipe\n");
// 	file_fd[0] = open(argv[1], O_RDONLY);
// 	if (file_fd[0] == -1)
// 		show_error("Error: Open file1 failed\n");
// 	file_fd[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
// 	if (file_fd[1] == -1)
// 		show_error("Error: Open file2 failed\n");
// 	pid = fork();
// 	if (pid == -1)
// 		show_error("Error: Fork\n");
// 	if (pid == 0)
// 		child_proc(&argv[2], envp, pipe_fd, file_fd);
// 	else
// 		parent_proc(&argv[3], envp, pipe_fd, file_fd);
// 	close(file_fd[0]);
// 	close(file_fd[1]);
// 	return (0);
// }