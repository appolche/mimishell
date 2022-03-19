/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallon </var/mail/lfallon>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:43:37 by lfallon           #+#    #+#             */
/*   Updated: 2022/03/19 15:43:41 by lfallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd_print(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	printf("%s\n", tmp);
	free(tmp);
	g_data.exit_status = 0;
}

void	ft_pwd(char **argv)
{
	int	i;

	if (!argv[1])
	{
		ft_pwd_print();
		return ;
	}
	if (argv[1][0] == '-' && (argv[1][1] != 'L' && argv[1][1] != 'P'))
	{
		printf("minishell: pwd: -%c: invalid option\n", argv[1][1]);
		printf("pwd: usage: pwd [-LP]\n");
		g_data.exit_status = 2;
		return ;
	}
	ft_pwd_print();
	return ;
}
