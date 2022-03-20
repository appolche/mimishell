/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_head.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallon </var/mail/lfallon>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:27:44 by lfallon           #+#    #+#             */
/*   Updated: 2022/03/19 17:28:10 by lfallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*struct_head(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp->prev)
		tmp = tmp->prev;
	envp = tmp;
	return (envp);
}

void	show_error(char *message)
{
	printf("%s\n", message);
	exit(1);
}
