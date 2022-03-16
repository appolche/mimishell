#include "minishell.h"

void pipe_parent_proc(int pipe_fd[2], pid_t pid)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
}

void pipe_child_proc(t_list *list, char **cmd, int pipe_fd[2], t_envp *envp)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	close(pipe_fd[1]);
	redirect_fd(list);
	if (is_my_command(list))
	{
		exec_my_cmd(list, envp);
		exit(1);
	}
	else
		ft_exec(cmd, envp);
}

void pipe_proc(t_list *list, char **cmd, t_envp *envp)
{
	pid_t pid;
	int pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		show_error("Error: Pipe\n");
	pid = fork();
	if (pid == -1)
		show_error("Error: Fork\n");
	if (pid == 0)
		pipe_child_proc(list, cmd, pipe_fd, envp);
	else
		pipe_parent_proc(pipe_fd, pid);
}

void built_in_funcs_proc(t_list *list, t_envp *envp)
{
	set_default_sig();
	while (list->next)
	{
		pipe_proc(list, list->cmd, envp);
		list = list->next;
	}
	redirect_fd(list);
	if (is_my_command(list))
	{
		exec_my_cmd(list, envp);
		exit(1);
	}
	else
		ft_exec(list->cmd, envp);
}

void pipe_cmd_proc(t_list *list, t_envp *envp)
{
	t_list *tmp;
	pid_t pid;

	if (list->cmd[0] == NULL)
		return;
	if (list->next == NULL && check_my_cmd(list->cmd))
	{
		exec_my_single_cmd(list, envp);
		return;
	}
	pid = fork();
	if (pid == -1)
		show_error("Error: Fork\n");
	disable_sig();
	if (pid == 0)
		built_in_funcs_proc(list, envp);
	else
		waitpid(pid, NULL, 0);
	set_custom_sig();
}