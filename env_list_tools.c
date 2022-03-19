/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfallon </var/mail/lfallon>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:26:33 by lfallon           #+#    #+#             */
/*   Updated: 2022/03/19 17:26:36 by lfallon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_lstnew(char *name, char *value)
{
	t_envp	*check;

	check = (t_envp *)malloc(sizeof(t_envp));
	if (!check)
		return (NULL);
	check->value = value;
	check->name = name;
	check->prev = NULL;
	check->next = NULL;
	return (check);
}

void	push_back(char *name, char *value, t_envp *check)
{
	t_envp	*next_node;

	next_node = (t_envp *)malloc(sizeof(t_envp));
	if (!next_node)
		exit(2);
	while (check->next)
		check = check->next;
	next_node->value = value;
	next_node->name = name;
	next_node->prev = check;
	next_node->next = NULL;
	check->next = next_node;
}

void	ft_lstclear(t_envp **lst)
{
	if (!lst || !(*lst))
		return ;
	if ((*lst)->next)
		ft_lstclear(&(*lst)->next);
	if ((*lst)->name)
		free((*lst)->name);
	if ((*lst)->value)
		free((*lst)->value);
	if (*lst)
		free(*lst);
	*lst = NULL;
}

void	free_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
		free(data->env[i++]);
	free(data->env);
}

t_envp	*search_name(t_envp *envp, char *name)
{
	t_envp	*tmp_head;
	int		i;

	tmp_head = envp;
	i = -1;
	while (tmp_head != NULL)
	{
		i = ft_strcmp(name, tmp_head->name);
		if (i == 0)
			break ;
		tmp_head = tmp_head->next;
	}
	if (i == -1)
		return (NULL);
	return (tmp_head);
}
