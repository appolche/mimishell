#include "minishell.h"

void pipe_parent_proc(int pipe_fd[2], pid_t pid)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	waitpid(pid, NULL, 0);
}

void pipe_child_proc(char **cmd, char **envp, int pipe_fd[2])
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	ft_exec(cmd, envp);
}

void pipe_proc(char **cmd, char **envp)
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
			pipe_proc(tmp->cmd, envp);
			tmp = tmp->next;
		}
		ft_exec(tmp->cmd, envp);
	}
	else
		waitpid(pid, NULL, 0);
}
