/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:10:26 by dleaves           #+#    #+#             */
/*   Updated: 2022/03/19 18:10:51 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_vopros(char *str, int i)
{
	int		start;
	char	*name;
	char	*value;
	char	*new_str;

	start = i;
	i += 1;
	name = ft_substr(str, start + 1, 1);
	value = ft_itoa(g_data.exit_status);
	new_str = cut_and_change_piece(str, start, name, value);
	free(value);
	free(name);
	return (new_str);
}

char	*new_str_cutter(char *str, int start, int *i, t_envp *envp)
{
	t_envp	*tmp;
	char	*new_str;
	char	*name;

	name = ft_substr(str, start + 1, *i - start - 1);
	tmp = search_name(envp, name);
	if (!tmp)
	{
		new_str = cut_cmd_piece(str, start, *i, ft_strlen(name));
		*i = start - 1;
		free(name);
		return (new_str);
	}
	*i = start + ft_strlen(tmp->value) - 1;
	free(name);
	return (cut_and_change_piece(str, start, tmp->name, tmp->value));
}

char	*ft_dollar(char *str, int *i, t_envp *envp)
{
	t_envp	*tmp;
	char	*name;
	char	*new_str;
	int		start;

	start = *i;
	if (str[*i] == '$' && str[*i + 1] == '?')
	{
		*i = *i - 2 + 1;
		return (dollar_vopros(str, start));
	}
	(*i)++;
	while (str[*i] && (str[*i] == '_' || ft_isalnum(str[*i])))
		(*i)++;
	return (new_str_cutter(str, start, i, envp));
}
