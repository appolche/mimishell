/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallon </var/mail/lfallon>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 20:24:37 by lfallon           #+#    #+#             */
/*   Updated: 2022/03/18 20:24:41 by lfallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_head(t_envp **envp)
{
	t_envp	*tmp;

	tmp = *envp;
	tmp->next->prev = NULL;
	free((*envp)->name);
	free((*envp)->value);
	free(*envp);
	*envp = tmp;
}

void	del_list(t_envp **envp)
{
	t_envp	*tmp;

	(*envp)->prev->next = (*envp)->next;
	(*envp)->next->prev = (*envp)->prev;
	tmp = struct_head((*envp));
	free((*envp)->name);
	free((*envp)->value);
	free(*envp);
	*envp = tmp;
}

void	del_last_list(t_envp **envp)
{
	(*envp)->prev->next = NULL;
	free((*envp)->name);
	free((*envp)->value);
	free(*envp);
}

void	delete_list(t_envp **list)
{
	if ((*list)->prev == NULL)
		del_head(&(*list));
	else if ((*list)->next == NULL)
		del_last_list(&(*list));
	else
		del_list(&(*list));
}
