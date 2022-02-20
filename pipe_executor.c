#include "minishell.h"


// static void	exec_my_command(t_main *main, t_commands *command)
// {
// 	if (!ft_strcmp(command->cmd[0], "echo"))
// 		main->exit_code = ft_echo(ft_mass_size(command->cmd), command->cmd);
// 	else if (!ft_strcmp(command->cmd[0], "env"))
// 		main->exit_code = ft_env(main);
// 	else if (!ft_strcmp(command->cmd[0], "pwd"))
// 		main->exit_code = ft_pwd(main);
// 	else if (!ft_strcmp(command->cmd[0], "export"))
// 		main->exit_code = ft_export(main, command);
// 	else if (!ft_strcmp(command->cmd[0], "unset"))
// 		main->exit_code = ft_unset(main, command);
// 	else if (!ft_strcmp(command->cmd[0], "cd"))
// 		main->exit_code = ft_cd(main, command);
// 	else if (!ft_strcmp(command->cmd[0], "exit"))
// 		ft_exit(main, command);
// 	if (main->exit_code != 0)
// 		main->flag_exit = 1;
// }

void show_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
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

void path_search(char **path, char **cmd, t_envp *envp)
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
			if (execve(final_path, cmd, envp) == -1) ///// ЖДУ ОТ САШИ Ф-ЦИЮ ДЛЯ ДВУМЕРНОГО МАССИВА envp
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

void ft_exec(char **cmd, t_envp *envp)
{
	char **path;
	int i;

	i = 0;
	path = NULL;
	if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
		absolute_path_exec(cmd, envp);

	while (envp)
	{
		if ((ft_strnstr(envp->name, "PATH", 4)))
		{
			path = ft_split(envp->value, ':');
			if (!path)
				exit(1);
			break;
		}
		envp = envp->next;
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

void pipe_child_proc(char **cmd, t_envp *envp, int pipe_fd[2])
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	ft_exec(cmd, envp);
}

void pipe_proc(char **cmd, t_envp *envp)
{
	pid_t pid;
	int pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		show_error("Error: Pipe\n");
	pid = fork();
	if (pid == -1)
		show_error("Error: Fork\n");
	if (pid == 0)
		pipe_child_proc(cmd, envp, pipe_fd);
	else
		pipe_parent_proc(pipe_fd, pid);
}

void pipe_cmd_proc(t_list *list, t_envp *envp)
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
			pipe_proc(tmp->cmd, envp);
			tmp = tmp->next;
		}
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