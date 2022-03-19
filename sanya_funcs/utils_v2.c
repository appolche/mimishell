/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_v2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallon </var/mail/lfallon>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:58:24 by lfallon           #+#    #+#             */
/*   Updated: 2022/03/19 15:58:27 by lfallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error_valid(char **argv, int i)
{
	char	*str;

	str = check_bracket(argv);
	if (str)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", str);
		free(str);
		g_data.exit_status = 258;
		return (1);
	}
	while (argv[i])
	{
		if (ft_isdigit_char(argv[i][0]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", argv[i]);
			g_data.exit_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	free_str(char *name, char *value)
{
	if (name)
		free(name);
	if (value)
		free(value);
}

char	*change_envp_error(char *str, int *i, int *j)
{
	char	*name;

	name = NULL;
	while (str[*i])
	{
		if (str[*i] == '=')
		{
			name = ft_substr(str, 0, *i);
			*j = *i;
			break ;
		}
		*i = *i + 1;
	}
	return (name);
}

int	change_envp(t_envp *envp, char *str)
{
	int		i;
	int		j;
	char	*name;
	char	*value;

	i = 0;
	j = 0;
	value = NULL;
	name = change_envp_error(str, &i, &j);
	if (name == NULL)
		return (0);
	if (search_name(envp, name))
	{
		while (str[i])
			i++;
		value = ft_substr(str, j + 1, i - j);
		change_envp_value(envp, name, value);
		g_data.exit_status = 0;
		free_str(name, value);
		return (1);
	}
	free_str(name, value);
	return (0);
}
