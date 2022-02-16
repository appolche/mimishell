#include "minishell.h"

static void swap(char **list, char **next)
{
    char *tmp_name;

    tmp_name = *list;
    *list = *next;
    *next = tmp_name;
}

void    swap_list(t_envp *list) // сортировка 
{
    t_envp *tmp;
    t_envp *tmp2;

    tmp = list;
    tmp2 = list;
    while (tmp)
    {
        tmp2 = struct_head(tmp2);
        while (tmp2->next)
        {
            if((ft_strcmp(tmp2->name, tmp2->next->name)) > 0)
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