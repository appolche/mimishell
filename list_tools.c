#include "minishell.h"

t_list *list_cmds(t_list **list, char *str)
{
    int i = 0;
    char **splitted_str;

    splitted_str = ft_split(str, '|');

    *list = create_list(splitted_str[i]);
    while (splitted_str[++i])
    {
        if (splitted_str[i][0])
            ft_push_back(*list, splitted_str[i]);
        else
            free(splitted_str[i]);
    }
    free (splitted_str);
    return (*list);
}

t_list *list_top(t_list *list)
{
    t_list *tmp;

    tmp = list;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    return (tmp);
}

t_list *create_list(char *content)
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
    {
        list = list->next;
    }
    list->next = node;
    node->prev = list;
    node->next = NULL;
    node->str = content;
}

void ft_pop_back(t_list **list)
{
    t_list *tmp_list;

    tmp_list = list_top(*list);
    if (tmp_list->prev)
        tmp_list->prev->next = NULL;
    else
        *list = NULL;
    free(tmp_list);
}

// t_list *ft_push_front(t_list *list, char *content)
// {
//     t_list *node;

//     node = (t_list *)malloc(sizeof(t_list));

//     if (list && list->prev == NULL)
//     {
//         node->prev = NULL;
//         node->next = list;
//         list->prev = node;
//     }
//     else 
//         node = create_list();
//     return (node);
// }

t_list *ft_pop_front(t_list *list)
{
    t_list *tmp;

    tmp = NULL;
    if (list && list->next)
    {
        tmp = list->next;
        list->next->prev = NULL;
    }
    free(list);
    return (tmp);
}

int find_list_size(t_list *list)
{
    t_list *tmp;
    int size;

    tmp = list;
    size = 0;
    while (tmp->next)
    {
        size++;
        tmp = tmp->next;
    }
    return (size);
}

// void free_frame(t_frame **frame)
// {
//     t_stack *tmp;
//     t_stack *st_a;
//     t_stack *st_b;

//     if ((*frame)->stack_a)
//     {
//         st_a = (*frame)->stack_a;
//         while (st_a)
//         {
//             tmp = (st_a)->next;
//             free(st_a);
//             st_a = tmp;
//         }
//     }
//     if ((*frame)->stack_b)
//     {
//         st_b = (*frame)->stack_b;
//         while (st_b)
//         {
//             tmp = (st_b)->next;
//             free(st_b);
//             st_b = tmp;
//         }
//     }
//     free(*frame);
// }