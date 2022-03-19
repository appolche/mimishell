/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:17:27 by dleaves           #+#    #+#             */
/*   Updated: 2022/03/19 17:18:13 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_each_node(t_list *list)
{
	while (list)
	{
		if (list->str_cmd)
			list->cmd = ft_split(list->str_cmd, ' ');
		list = list->next;
	}
}

void	check_redir(t_list *list, int *i)
{
	if (list->str_cmd[*i] == '>' || list->str_cmd[*i] == '<')
	{
		printf("list->str_cmd before cut: %s\n", list->str_cmd);
		list->str_cmd = split_cmd_redir(list, list->str_cmd, *i);
		printf("list->str_cmd after cut: %s\n", list->str_cmd);
		(*i)--;
	}
	else
		return ;
}

int	parse_list(t_envp *envp, t_list *list)
{
	int	i;

	while (list)
	{
		list->str_cmd = ft_strtrim(list->str, " ");
		i = -1;
		while (list->str_cmd[++i])
		{
			if (list->str_cmd[i] == '\'')
				list->str_cmd = ft_single_quotes(list->str_cmd, &i);
			else if (list->str_cmd[i] == '\"')
				list->str_cmd = ft_double_quotes(list->str_cmd, &i, envp);
			if (list->str_cmd[i] == '$')
				list->str_cmd = ft_dollar(list->str_cmd, &i, envp);
			check_redir(list, &i);
		}
		if (list->str_redir)
			parse_redirect(list, ft_strtrim(list->str_redir, " "));
		list = list->next;
	}
	return (1);
}

int	str_check_loop(char *str, t_list **list, int *i, int *j)
{
	while (str[++(*i)])
	{
		if (str[*i] == '\'')
		{
			if (check_unclosed_quotes(str, i, '\''))
				return (0);
		}
		else if (str[*i] == '\"')
		{
			if (check_unclosed_quotes(str, i, '\"'))
				return (0);
		}
		if ((str[*i] == '>' || str[*i] == '<') && redir_syntax_errors(str, *i))
			return (0);
		if (str[*i] == '|')
		{
			if (syntax_errors(str, *i))
				return (0);
			*list = create_list(*list, str, *i, *j);
			*j = *i;
		}
	}
	return (1);
}

int	split_for_list(char *str, t_list **list)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (prepars_syntax_errors(str))
		return (0);
	if (str_check_loop(str, list, &i, &j))
	{
		*list = create_list(*list, str, i, j);
		make_null_init(*list);
		free(str);
		return (1);
	}
	else
	{
		free(str);
		return (0);
	}
}
