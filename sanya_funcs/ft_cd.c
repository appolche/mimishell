/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallon </var/mail/lfallon>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:19:52 by lfallon           #+#    #+#             */
/*   Updated: 2022/03/18 20:19:56 by lfallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_pwd(t_envp *envp)
{
	if (!search_name(envp, "PWD"))
		push_back(ft_strdup("PWD"), ft_strdup(""), envp);
	if (!search_name(envp, "OLDPWD"))
		push_back(ft_strdup("OLDPWD"), ft_strdup(""), envp);
	return ;
}

char	*cd_home(t_envp *envp)
{
	t_envp	*home;
	char	*tmp;

	home = search_name(envp, "HOME");
	if (!home)
	{
		printf("minishell: cd: HOME not set\n");
		g_data.exit_status = 1;
		return (NULL);
	}
	tmp = home->value;
	return (tmp);
}

void	change_envp_value(t_envp *envp, char *name, char *value)
{
	envp = search_name(envp, name);
	if (envp)
	{
		if (envp->value)
			free(envp->value);
		envp->value = ft_strdup(value);
	}
}

void	ft_cd_next_step(t_envp *envp, char *command)
{
	char	*old_pwd;
	char	*new_pwd;

	check_pwd(envp);
	old_pwd = getcwd(NULL, 0);
	if (chdir(command) == 0)
	{
		change_envp_value(envp, "OLDPWD", old_pwd);
		free(old_pwd);
		new_pwd = getcwd(NULL, 0);
		change_envp_value(envp, "PWD", new_pwd);
		free(new_pwd);
		g_data.exit_status = 0;
	}
	else
	{
		free(old_pwd);
		printf("minishell: cd: %s: No such file or directory\n", command);
		g_data.exit_status = 1;
	}
}

void	ft_cd(t_envp *envp, char **command)
{
	int		i;
	char	*home;

	i = array_len(command);
	if (i > 1)
	{
		printf("minishell: cd: too many arguments\n");
		g_data.exit_status = 1;
		return ;
	}
	if (command[1] == NULL)
	{
		home = cd_home(envp);
		if (!home)
			return ;
		check_pwd(envp);
		ft_cd_next_step(envp, home);
	}
	else
		ft_cd_next_step(envp, command[1]);
}
