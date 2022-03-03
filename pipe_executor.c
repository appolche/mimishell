#include "minishell.h"

static void	exec_my_cmd(t_data *data, t_list *list)
{
	if (!ft_strcmp(list->cmd[0], "echo"))
		ft_echo(list->cmd);
	else if (!ft_strcmp(list->cmd[0], "env"))
		ft_env(list->cmd, data->envp);
	else if (!ft_strcmp(list->cmd[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(list->cmd[0], "export"))
		ft_export(list->cmd);
	else if (!ft_strcmp(list->cmd[0], "unset"))
		ft_unset(list->cmd);
	else if (!ft_strcmp(list->cmd[0], "cd"))
		ft_cd(list->cmd);
	else if (!ft_strcmp(list->cmd[0], "exit"))
		ft_exit(list->cmd);
}

void redirect_fd(t_list *list)
{
    if (list->file_fd[0] != -1)
        dup2(list->file_fd[0], 0);
    if (list->file_fd[1] != -1)
        dup2(list->file_fd[1], 1); //добавить проверки на dup;
}

void show_error(char *message)
{
	printf("%s\n", message);
	exit(1);
}

void absolute_path_exec(char **cmd, char **envp)
{
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
			show_error("Error: Cmd execution failed\n");
	}
	printf("Error: Path not found\n");
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
		// printf("%s\n", final_path);
		if (access(final_path, X_OK) == 0)
		{
			if (execve(final_path, cmd, envp) == -1)
			{
				malloc_free(path);
				free(final_path);
				show_error("Error: Cmd execution failed\n");
			}
		}
		if (final_path)
			free(final_path);
	}
	if (path)
		malloc_free(path);
	exit(1);
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

void pipe_parent_proc(int pipe_fd[2], pid_t pid)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	waitpid(pid, NULL, 0);
}

void pipe_child_proc(t_list *list, char **cmd, char **envp, int pipe_fd[2])
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	redirect_fd(list);
	ft_exec(cmd, envp);
}

void pipe_proc(t_list *list, char **cmd, char **envp)
{
	pid_t pid;
	int pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		show_error("Error: Pipe\n");
	pid = fork();
	if (pid == -1)
		show_error("Error: Fork\n");
	if (pid == 0)
		pipe_child_proc(list, cmd, envp, pipe_fd);
	else
		pipe_parent_proc(pipe_fd, pid);
}


void pipe_cmd_proc(t_list *list, char **envp)
{
	t_list *tmp;
	pid_t pid;

	tmp = list;
	pid = fork();
	if (pid == -1)
		show_error("Error: Fork\n");
	if (pid == 0)
	{
		while (tmp->next)
		{
			pipe_proc(tmp, tmp->cmd, envp);
			tmp = tmp->next;
		}
		redirect_fd(tmp);
		ft_exec(tmp->cmd, envp);
	}
	else
		waitpid(pid, NULL, 0);
}

// void one_cmd_proc(char **cmd, char **env)
// {
// 	pid_t pid;

// 	pid = fork();
// 	if (pid == -1)
// 		show_error("Error: Fork\n");
// 	if (pid == 0)
// 		ft_exec(cmd, env);
// 	else
// 		waitpid(pid, NULL, 0);
// }