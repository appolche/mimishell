/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_cutters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:23:41 by dleaves           #+#    #+#             */
/*   Updated: 2022/03/19 17:25:44 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_cmd_piece(char *str, int start, int i, int size)
{
	char	*tmp2;
	char	*tmp3;
	char	*new_str;

	tmp2 = ft_substr(str, 0, start);
	tmp3 = ft_substr(str, i, ft_strlen(str) - start - size);
	if (!tmp2 || !tmp3)
		return (NULL);
	new_str = ft_strjoin(tmp2, tmp3);
	if (!new_str)
		return (NULL);
	free(str);
	return (new_str);
}

int	skip_some_chars(char *str, int i)
{
	i++;
	if (str[i] == '>' || str[i] == '<')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	return (i);
}

char	*cut_and_change_piece(char *str, int start, char *name, char *value)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		size;

	size = 0;
	size = ft_strlen(name) + 1;
	tmp = ft_substr(str, 0, start);
	tmp2 = ft_strdup(value);
	tmp3 = ft_substr(str, start + size, ft_strlen(str) - start - size);
	if (!tmp || !tmp2)
		return (NULL);
	tmp = ft_strjoin(tmp, tmp2);
	if (!tmp)
		return (NULL);
	tmp = ft_strjoin(tmp, tmp3);
	if (!tmp)
		return (NULL);
	free(str);
	return (tmp);
}

char	*cut_quotes(char *str, int start, int end)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_substr(str, 0, start);
	tmp2 = ft_substr(str, start + 1, end - start - 1);
	tmp3 = ft_substr(str, end + 1, ft_strlen(str) - end);
	if (!tmp || !tmp2 || !tmp3)
		return (NULL);
	tmp = ft_strjoin(tmp, tmp2);
	if (!tmp)
		return (NULL);
	tmp = ft_strjoin(tmp, tmp3);
	if (!tmp)
		return (NULL);
	return (tmp);
}
