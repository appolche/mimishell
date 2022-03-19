/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cmd_proc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:16:24 by dleaves           #+#    #+#             */
/*   Updated: 2022/03/19 17:17:14 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_my_single_cmd(t_list *list, t_envp *envp)
{
	if (!ft_strcmp(list->cmd[0], "export"))
		ft_export(&envp, list->cmd);
	else if (!ft_strcmp(list->cmd[0], "unset"))
		ft_unset(&envp, list->cmd);
	else if (!ft_strcmp(list->cmd[0], "cd"))
		ft_cd(envp, list->cmd);
	else if (!ft_strcmp(list->cmd[0], "exit"))
		ft_exit(list->cmd);
	else if (!ft_strcmp(list->cmd[0], "pwd"))
		ft_pwd(list->cmd);
	else if (!ft_strcmp(list->cmd[0], "echo"))
		ft_echo(list->cmd);
	// redirect_fd(list);
}

int	check_my_cmd(char **cmd)
{
	if (!ft_strcmp(cmd[0], "echo")
		|| !ft_strcmp(cmd[0], "pwd")
		|| !ft_strcmp(cmd[0], "exit")
		|| !ft_strcmp(cmd[0], "export")
		|| !ft_strcmp(cmd[0], "unset")
		|| !ft_strcmp(cmd[0], "cd"))
		return (1);
	return (0);
}

void	exec_my_cmd(t_list *list, t_envp *envp)
{
	if (!ft_strcmp(list->cmd[0], "echo"))
		ft_echo(list->cmd);
	else if (!ft_strcmp(list->cmd[0], "env"))
		ft_env(envp, list->cmd);
	else if (!ft_strcmp(list->cmd[0], "pwd"))
		ft_pwd(list->cmd);
}

int	is_my_command(t_list *list)
{
	if (!ft_strcmp(list->cmd[0], "echo")
		|| !ft_strcmp(list->cmd[0], "env")
		|| !ft_strcmp(list->cmd[0], "export")
		|| !ft_strcmp(list->cmd[0], "unset")
		|| !ft_strcmp(list->cmd[0], "pwd")
		|| !ft_strcmp(list->cmd[0], "cd"))
		return (1);
	return (0);
}
