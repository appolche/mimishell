/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_redir_cutters.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:26:15 by dleaves           #+#    #+#             */
/*   Updated: 2022/03/19 17:27:07 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_str_redir(t_list *list, char *str, int i, int start)
{
	char	*tmp;
	char	*tmp2;
	char	*new_str;

	tmp = ft_substr(str, start, i - start);
	tmp2 = ft_strdup(tmp);
	if (!list->str_redir)
		list->str_redir = tmp;
	else
		list->str_redir = ft_strjoin(list->str_redir, tmp);
	new_str = cut_cmd_piece(str, start, i, ft_strlen(tmp2));
	free(tmp2);
	return (new_str);
}

char	*split_cmd_redir(t_list *list, char *str, int i)
{
	int	start;

	start = i;
	i = skip_some_chars(str, i);
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (check_unclosed_quotes(str, &i, '\''))
				return (NULL);
		}
		else if (str[i] == '\"')
		{
			if (check_unclosed_quotes(str, &i, '\"'))
				return (NULL);
		}
		if (str[i] == ' ')
			break ;
		i++;
	}
	return (cut_str_redir(list, str, i, start));
}

char	*filename_in_quotes(char *str, int *i, int c)
{
	char	*file_name;
	int		quote_start;

	quote_start = *i;
	while (str[++(*i)])
	{
		if (str[*i] == c)
			break ;
	}
	file_name = ft_substr(str, quote_start + 1, *i - quote_start - 1);
	return (file_name);
}

char	*get_file_name(char *str, int i, int *ret)
{
	char	*file_name;
	int		start;
	int		quote_start;

	while (str[i] && str[i] == ' ')
		i++;
	start = i;
	if (str[i] == '\'')
		file_name = filename_in_quotes(str, &i, '\'');
	else if (str[i] == '\"')
		file_name = filename_in_quotes(str, &i, '\"');
	else
	{
		while (str[i])
		{
			if (str[i] == ' ' || str[i] == '>' || str[i] == '<'
				|| str[i] == '\'' || str[i] == '\"')
				break ;
			i++;
		}
		file_name = ft_substr(str, start, i - start);
	}
	*ret = i;
	return (file_name);
}
