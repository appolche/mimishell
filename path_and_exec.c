#include "minishell.h"

void show_error(char *message)
{
	printf("%s\n", message);
	exit(1);
}

char **make_env_array(t_envp *envp) //
{
	char **array_env;
    char *tmp;
    char *string;
    int i;

    tmp = ft_strdup("=");
    array_env = (char **)malloc((size_list(envp) + 1) * sizeof(char *));
    if (!array_env)
        return (NULL);
    i = 0;
    while (envp)
    {
        string = ft_strjoin2(envp->name, tmp);
        array_env[i] = ft_strjoin2(string, envp->value);
        free(string);
        i++;
        envp = envp->next;
    }
    array_env[i] = NULL;
    free(tmp);
    return (array_env);
}

void absolute_path_exec(char **cmd, char **envp)
{
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
			show_error("Error: Cmd execution failed\n");
	}
	printf("minishell: %s: No such file or directory\n", cmd[0]);
	data.exit_status = 127;
	exit(127);
}

void path_search(char **path, char **cmd, char **envp)
{
	char *final_path;
	char *tmp;
	char *tmp2;
	char *tmp3;
	int j;

	j = 0;
	while (path[++j])
	{
		tmp3 = ft_strdup(path[j]);
		tmp = ft_strjoin(tmp3, ft_strdup("/"));
		tmp2 = ft_strdup(cmd[0]);
		final_path = ft_strjoin(tmp, tmp2);
		if (access(final_path, X_OK) == 0)
		{
			if (execve(final_path, cmd, envp) == -1)
			{
				printf("minishell: %s: command not found\n", cmd[0]);
				malloc_free(path);
				free(final_path);
				data.exit_status = 127;
				exit(127);
			}
		}
		if (final_path)
			free(final_path);
	}
	printf("minishell: %s: command not found\n", cmd[0]);
	if (path)
		malloc_free(path);
	data.exit_status = 127;
	exit(127);
}

void ft_exec(char **cmd, t_envp *env_list)
{
	char **path;
	char **envp;
	int i;

	i = 0;
	path = NULL;
	envp = make_env_array(env_list);
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
	printf("minishell: %s: No such file or directory\n", cmd[0]);
	data.exit_status = 127;
	exit(127);
}
