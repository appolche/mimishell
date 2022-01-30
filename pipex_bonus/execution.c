#include "pipex.h"

void	absolute_path_exec(char **cmd, char **envp)
{
	if (!access(cmd[0], X_OK))
	{
		if (execve(cmd[0], cmd, envp) == -1)
			malloc_free(cmd);
		show_error("Error: Cmd execution failed\n");
	}
	malloc_free(cmd);
	ft_putstr_fd("Error: Path not found\n", 2);
}

void	path_search(char **path, char **cmd, char **envp)
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

void	ft_exec(char **cmd, char **envp)
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
			if (!path)
				exit(1);
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
