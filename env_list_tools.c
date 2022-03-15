#include "minishell.h"

t_envp *ft_lstnew(char *name, char *value) 
{
	t_envp *check;

	if (!(check = (t_envp *)malloc(sizeof(t_envp))))
		return (NULL);
	check->value = value;
    check->name = name;
	check->prev = NULL;
	check->next = NULL;
	return (check);
}

void push_back(char *name, char *value, t_envp *check)
{
	t_envp *next_node;

	if (!(next_node = (t_envp *)malloc(sizeof(t_envp))))
		exit (2);
	while (check->next)
        check = check->next;
	next_node->value = value;
    next_node->name = name;
	next_node->prev = check;
	next_node->next = NULL;
	check->next = next_node;
}

void	ft_lstclear(t_envp **lst) // очищение t_envp
{
	if (!lst || !(*lst))
		return ;
	ft_lstclear(&(*lst)->next);
	free((*lst)->name);
	free((*lst)->value);
	free(*lst);
	*lst = NULL;
}

void free_env(t_data *data) // очищение t_data
{
    int i;

    i = 0;
    while (data->env[i])
        free(data->env[i++]);
    free(data->env);
}

t_envp *search_name(t_envp *envp, char *name) // функция поиска по структуре envp
{
    t_envp *tmp_head;
    int i;

    tmp_head = envp;
    i = -1;
    while (tmp_head != NULL)
    {
        i = ft_strcmp(name, tmp_head->name);
        if (i == 0)            
            break;
        tmp_head = tmp_head->next;
    }
    if (i == -1)
        return (NULL);
    return (tmp_head); // обработать на NULL
}

t_envp *struct_head(t_envp *envp) //вспомогательная фун-ия для поиска головы
{
    t_envp *tmp;

    tmp = envp;
    while(tmp->prev)
        tmp = tmp->prev;
    envp = tmp;
    return (envp);
}