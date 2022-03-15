#include "minishell.h"

void make_null_init(t_list *list)
{
    while (list)
    {
        list->str_cmd = NULL;
        list->str_redir = NULL;
        list->cmd = NULL;
        list->file_fd[0] = -1;
        list->file_fd[1] = -1;
        list->heredoc = -1;
        list = list->next;
    }
}

t_list *create_list(t_list *list, char *str, int i, int j)
{
    
    if (!list)
        list = create_head(ft_substr(str, 0, i));
    else
        ft_push_back(list, ft_substr(str, j + 1, i - j - 1));
    return (list);
}

t_list *create_head(char *content)
{
    t_list *node;

    node = (t_list *)malloc(sizeof(t_list));
    if (!node)
        return (NULL);
    node->next = NULL;
    node->prev = NULL;
    node->str = content;
    return (node);
}

void ft_push_back(t_list *list, char *content)
{
    t_list *node;

    node = (t_list *)malloc(sizeof(t_list));
    while (list->next)
        list = list->next;
    list->next = node;
    node->prev = list;
    node->next = NULL;
    node->str = content;
}

void free_list(t_list **list)
{
    t_list *tmp;

    if (!list || !(*list))
        return;
    while (*list)
    {
        tmp = (*list)->next;
        if ((*list)->str)
            free((*list)->str);
        if ((*list)->str_cmd)
            free((*list)->str_cmd);
        if ((*list)->str_redir)
            free((*list)->str_redir);
        if ((*list)->cmd)
            malloc_free((*list)->cmd);
        free(*list);
        *list = tmp;
    }
    // free(*list);
}