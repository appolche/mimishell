/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallon <lfallon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:38:23 by lfallon           #+#    #+#             */
/*   Updated: 2022/03/18 23:03:41 by lfallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcheck(const char *s1, const char s2)
{
	const unsigned char	*p1;

	p1 = (const unsigned char *)s1;
	while (*p1)
	{
		if (*p1 == s2)
			return (1);
		++p1;
	}
	return (0);
}

char	*check_bracket(char **av)
{
	int		i;
	char	*tmp;

	i = 0;
	if (av[1][0] == '(')
	{
		return (ft_word(av[1]));
	}
	while (av[i])
	{
		tmp = check_bracket_v2(av[i]);
		if (tmp)
			return (tmp);
		i++;
	}
	free(tmp);
	return (NULL);
}

int	ft_isalldigit(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit((unsigned char)str[i]) || ft_strlen(str) >= 19)
			return (1);
		i++;
	}
	return (0);
}

void	ft_out(int value, int flag, char *av)
{
	rl_clear_history();
	g_data.exit_status = (unsigned char)value;
	printf("exit\n");
	if (flag == 1)
		printf("minishell: exit: %s: numeric argument required\n", av);
	if (flag == 2)
	{
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	exit(value);
}

void	ft_exit(char **av)
{
	int		i;
	char	*str;

	if (!av)
		exit(0);
	i = array_len(av);
	if (i == 0)
		ft_out(0, 0, NULL);
	str = check_bracket(av);
	if (str)
	{
		printf("minishell: syntax error near unexpected token `%s'\n", str);
		free(str);
		g_data.exit_status = 258;
		exit(258);
	}
	if (i >= 1)
	{
		if (ft_isalldigit(av[1]) && i == 1)
			ft_out(255, 1, av[1]);
		else if (i >= 2)
			ft_out(1, 2, NULL);
		else
			ft_out((unsigned char)ft_atoi(av[1]), 0, NULL);
	}
}
