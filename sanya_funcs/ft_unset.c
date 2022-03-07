#include "../minishell.h"

void del_head(t_envp **envp)
{
    t_envp *tmp;

    tmp = *envp;
    tmp->next->prev = NULL;
    free((*envp)->name);
    free((*envp)->value);
    free(*envp);
    *envp = tmp;
}

void del_list(t_envp **envp)
{
    t_envp *tmp;

    (*envp)->prev->next = (*envp)->next;
    (*envp)->next->prev = (*envp)->prev;
     tmp = struct_head((*envp));
    
    free((*envp)->name);
    free((*envp)->value);
    free(*envp);
    *envp = tmp;  
}

void del_last_list(t_envp **envp)
{
    (*envp)->prev->next = NULL;
    free((*envp)->name);
    free((*envp)->value);
    free(*envp);
}

void delete_list(t_envp **list)
{
    if ((*list)->prev == NULL)
        del_head(&(*list));
    else if((*list)->next == NULL)
        del_last_list(&(*list));
    else
        del_list(&(*list));
}

void ft_unset_next_step(t_envp **envp, char *name) // удаление переменой 
{
    t_envp *tmp;

    tmp = *envp;
    tmp = search_name(tmp, name);
    if(!tmp)
    {
        printf("\n");
        return ;
    }
    delete_list(&tmp);
    *envp = struct_head(tmp);
}

void ft_unset(t_envp **envp, char **name)
{
    int i;

    i = 0;
    while(name[++i])
        ft_unset_next_step(envp, name[i]);
    data->exit_status = 0;
}