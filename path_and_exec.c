/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:18:43 by dleaves           #+#    #+#             */
/*   Updated: 2022/03/19 17:20:16 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_error(char *message)
{
	printf("%s\n", message);
	exit(1);
}

char	**make_env_array(t_envp *envp)
{
	char	**array_env;
	char	*tmp;
	char	*string;
	int		i;

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

void	absolute_path_exec(char **cmd, char **envp)
{
	if (access(cmd[0], X_OK) == 0)
	{
		if (execve(cmd[0], cmd, envp) == -1)
			printf("minishell: %s: command not found\n", cmd[0]);
	}
	printf("minishell: %s: No such file or directory\n", cmd[0]);
	exit(127);
}

void	path_search(char **path, char **cmd, char **envp)
{
	char	*final_path;
	char	*tmp;
	int		j;

	j = 0;
	while (path[++j])
	{
		tmp = ft_strjoin(ft_strdup(path[j]), ft_strdup("/"));
		final_path = ft_strjoin(tmp, ft_strdup(cmd[0]));
		if (access(final_path, X_OK) == 0)
		{
			if (execve(final_path, cmd, envp) == -1)
			{
				malloc_free(path);
				free(final_path);
				exit(127);
			}
		}
		if (final_path)
			free(final_path);
	}
	printf("minishell: %s: command not found\n", cmd[0]);
	if (path)
		malloc_free(path);
	exit(127);
}

void	ft_exec(char **cmd, t_envp *env_list)
{
	char	**path;
	char	**envp;
	int		i;

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
				exit(127);
			break ;
		}
		i++;
	}
	if (path)
		path_search(path, cmd, envp);
	printf("minishell: %s: No such file or directory\n", cmd[0]);
	exit(127);
}
