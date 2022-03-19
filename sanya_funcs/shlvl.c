/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallon </var/mail/lfallon>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 20:59:34 by lfallon           #+#    #+#             */
/*   Updated: 2022/03/16 20:59:39 by lfallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mass(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	check_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit_char(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	shlvl_value_2(t_envp *envp, t_envp *check)
{
	int	i;

	i = ft_atoi(check->value) + 1;
	if (i == 1000)
	{
		free(check->value);
		check->value = NULL;
	}
	else if (i >= 1001)
	{
		printf("minishell: warning: shell level (1001) ");
		printf("too high, resetting to 1\n");
		free(check->value);
		check->value = ft_itoa(1);
	}
	else
	{
		free(check->value);
		check->value = ft_itoa(i);
	}
	envp = struct_head(check);
	return ;
}

void	shlvl_value(t_envp *envp, t_envp *check)
{
	int	i;

	if (check_value(check->value) == 0)
	{
		free(check->value);
		check->value = ft_itoa(1);
		envp = struct_head(check);
		return ;
	}
	else
	{
		shlvl_value_2(envp, check);
		return ;
	}
}

void	ft_shlvl(t_envp *envp)
{
	char	*name;
	char	*value;
	t_envp	*check;

	g_data.exit_status = 0;
	check = search_name(envp, "SHLVL");
	if (!check)
	{
		name = ft_strdup("SHLVL");
		value = ft_strdup("0");
		push_back(name, value, envp);
		return ;
	}
	if (!check->value)
	{
		check->value = ft_itoa(0);
		envp = struct_head(check);
		return ;
	}
	else
		shlvl_value(envp, check);
	return ;
}
