/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallon </var/mail/lfallon>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 21:51:03 by lfallon           #+#    #+#             */
/*   Updated: 2022/03/15 21:51:10 by lfallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_flag(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[0] == '-')
		{
			j = 1;
			while (str[j] && str[j] == 'n')
			{
				if (str[j + 1] == '\0')
					return (j);
				j++;
			}
		}
		i++;
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	print_echo(int flag, char **av)
{
	int	i;

	if (flag)
		i = 2;
	else
		i = 1;
	while (av[i])
	{
		if (flag)
		{
			ft_putstr_fd((av[i]), 1);
			if (av[i + 1])
				write(1, " ", 1);
		}
		else
		{
			ft_putstr_fd(av[i], 1);
			if (av[i + 1])
				write(1, " ", 1);
			else
				write(1, "\n", 1);
		}
		i++;
	}
}

void	ft_echo(char **av)
{
	int	flag;
	int	i;

	i = array_len(av);
	if (i == 0)
	{
		printf("\n");
		data.exit_status = 0;
		return ;
	}
	flag = check_flag(av[1]);
	if (flag && i == 1)
	{
		printf("\r");
		data.exit_status = 0;
		return ;
	}
	print_echo(flag, av);
	data.exit_status = 0;
	return ;
}
