#include "minishell.h"

void show_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}

static char **malloc_free(char **smth)
{
	unsigned int i;

	i = 0;
	while (smth[i])
		free(smth[i++]);
	free(smth);
	return (NULL);
}

void absolute_path_exec(char **cmd, char **envp)
{
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
			malloc_free(cmd);
		//show_error("Error: Cmd execution failed\n");
	}
	malloc_free(cmd);
	ft_putstr_fd("Error: Path not found\n", 2);
}

void path_search(char **path, char **cmd, char **envp)
{
	char *final_path;
	char *tmp;
	int j;

	j = 0;
	while (path[++j])
	{
		tmp = ft_strjoin(path[j], "/");
		final_path = ft_strjoin(tmp, cmd[0]);
		//printf("%s\n", final_path);
		free(tmp);
		if (access(final_path, X_OK) == 0)
		{
			//printf("path: %s accessed\n", final_path);
			if (execve(final_path, cmd, envp) == -1)
			{
				malloc_free(path);
				// malloc_free(cmd);
				if (final_path)
					free(final_path);
				//show_error("Error: Cmd execution failed\n");
			}
			//printf("Error: access failed\n");
		}
		if (final_path)
			free(final_path);
	}
	printf("minishell: %s: command not found\n", cmd[0]);
	if (path)
		malloc_free(path);
	exit (1);
}

void ft_exec(char **cmd, char **envp)
{
	char **path;
	int i;

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
			break;
		}
		i++;
	}
	if (path)
		path_search(path, cmd, envp);
	// else
	// 	show_error("Error: Path not found\n");
	// if (cmd)
	// 	malloc_free(cmd);
	
}

void one_cmd_proc(char **cmd, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		show_error("Error: Fork\n");
	if (pid == 0)
		ft_exec(cmd, env);
	else
		waitpid(pid, NULL, 0);
}