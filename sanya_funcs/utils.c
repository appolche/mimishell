/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallon </var/mail/lfallon>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:59:43 by lfallon           #+#    #+#             */
/*   Updated: 2022/03/19 15:59:55 by lfallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit_char(char c)
{
	return (c >= '0' && c <= '9');
}

void	print_export(t_envp *list)
{
	while (list)
	{
		if (list->value == NULL)
			printf("declare -x %s=\"\"\n", list->name);
		else
			printf("declare -x %s=\"%s\" \n", list->name, list->value);
		list = list->next;
	}
}

int	array_len(char **av)
{
	int	i;

	i = 0;
	if (!av[1])
		return (0);
	while (av[i])
		i++;
	return (i - 1);
}

char	*ft_word(char *str)
{
	int		i;
	int		j;
	char	*word;

	word = malloc(ft_strlen(str) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
			i++;
		word[j++] = str[i++];
	}
	word[j] = '\0';
	return (word);
}

char	*check_bracket_v2(char *av)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strcheck(av, '('))
	{
		tmp = ft_strdup("(");
		return (tmp);
	}
	if (ft_strcheck(av, ')'))
	{
		tmp = ft_strdup("(");
		return (tmp);
	}
	return (tmp);
}
