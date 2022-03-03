#include "../minishell.h"

void ft_env(t_envp *envp)
{
    t_envp *tmp;
    tmp = envp;

    while(tmp->next)
    {
        if(tmp->value == NULL)
            tmp = tmp->next;
        else
        {
            printf("%s=%s\n", tmp->name, tmp->value);
                tmp = tmp->next;
        } 
    }   
}

// провекра на корректные аргументы
// dleaves@dleaves42:~/projects/git-mimi-01-03$ env fdkh
// env: ‘fdkh’: No such file or directory