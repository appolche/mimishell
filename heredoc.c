/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:13:05 by dleaves           #+#    #+#             */
/*   Updated: 2022/03/19 17:13:46 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_here_doc(int sig)
{
	(void)sig;
	exit(1);
}

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
	disable_sig();
	if (pid == 0)
	{
		rl_catch_signals = 1;
		set_default_sig();
		signal(SIGINT, exit_here_doc);
		here_doc_child(pipe_fd, limiter);
	}
	close(pipe_fd[1]);
	waitpid(pid, &g_data.exit_status, WNOHANG & WUNTRACED);
	if (WIFEXITED(g_data.exit_status))
		g_data.exit_status = WEXITSTATUS(g_data.exit_status);
	set_custom_sig();
	return (pipe_fd[0]);
}
