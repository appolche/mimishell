#include "minishell.h"

char *cut_and_change_piece(char *str, int start, char *name, char *value) //мб убрать?
{
    char *tmp;
    char *tmp2;
    char *tmp3;
    int  size;

    size = 0;
    size = ft_strlen(name) + 1;
    tmp = ft_substr(str, 0, start);
    tmp2 = ft_strdup(value);
    tmp3 = ft_substr(str, start + size, ft_strlen(str) - start - size);
    if (!tmp || !tmp2)
        return (NULL);
    tmp = ft_strjoin(tmp, tmp2);
    if (!tmp)
        return (NULL);
    tmp = ft_strjoin(tmp, tmp3);
    if (!tmp)
        return (NULL);
    free(str);
    return (tmp);
}

char    *ft_dollar(char *str, int *i, t_envp *envp)
{
    //должен вылетать при вводе направильной переменной без одинарных кавычек (при двойных тодже вылетает)
    int start;
    t_envp *tmp;
    char *name;
    char *value;
    char *new_str;

    start = *i;
    tmp = envp;
    (*i)++;
    while (str[*i] && (str[*i] == '_' || ft_isalnum(str[*i])))
        (*i)++;
    name = ft_substr(str, start + 1, *i - start - 1);
    if (!name)
        return (NULL);
    while (tmp)
    {
        if (ft_strcmp(tmp->name, name) == 0)
            break;
        tmp = tmp->next;
    }
    if (!tmp)
    {
        free(name);
        free(str);
        return (NULL);
    }
    new_str = cut_and_change_piece(str, start, tmp->name, tmp->value);
    *i = start + ft_strlen(tmp->value) - 1;
    free(name);
    return (new_str);
}
