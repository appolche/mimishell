/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_val_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallon </var/mail/lfallon>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:30:04 by lfallon           #+#    #+#             */
/*   Updated: 2022/03/19 17:30:07 by lfallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	swap(char **list, char **next)
{
	char	*tmp_name;

	tmp_name = *list;
	*list = *next;
	*next = tmp_name;
}

void	swap_list(t_envp *list)
{
	t_envp	*tmp;
	t_envp	*tmp2;

	tmp = list;
	tmp2 = list;
	while (tmp)
	{
		tmp2 = struct_head(tmp2);
		while (tmp2->next)
		{
			if ((ft_strcmp(tmp2->name, tmp2->next->name)) > 0)
			{
				swap(&(tmp2->name), &(tmp2->next->name));
				swap(&(tmp2->value), &(tmp2->next->value));
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	list = struct_head(tmp2);
	print_export(list);
}
