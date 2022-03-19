/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallon </var/mail/lfallon>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:46:13 by lfallon           #+#    #+#             */
/*   Updated: 2022/03/19 15:46:17 by lfallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset_next_step(t_envp **envp, char *name)
{
	t_envp	*tmp;

	tmp = *envp;
	tmp = search_name(tmp, name);
	if (!tmp)
	{
		printf("");
		return ;
	}
	delete_list(&tmp);
	*envp = struct_head(tmp);
}

void	ft_unset(t_envp **envp, char **name)
{
	int	i;

	i = 0;
	while (name[++i])
		ft_unset_next_step(envp, name[i]);
	g_data.exit_status = 0;
}
