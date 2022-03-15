#include "minishell.h"

char *dollar_vopros(char *str, int i)
{
    int start;
    char *name;
    char *value;
    char *new_str;

    start = i;
    i += 1;
    name = ft_substr(str, start + 1, i - start);
    printf("name: /%s/\n", name);
    value = ft_itoa(data.exit_status);
    printf("value: /%s/\n", value);
    new_str = cut_and_change_piece(str, start, name, value);
    free(value);
    return (new_str);
}

char    *ft_dollar(char *str, int *i, t_envp *envp)
{
    //должен вылетать при вводе направильной переменной без одинарных кавычек (при двойных тодже вылетает)
    int start;
    t_envp *tmp;
    char *name;
    char *new_str;

    if (str[*i] == '$' && str[*i + 1] == '?')
    {
        new_str = dollar_vopros(str, *i);
        *i += 1;
        return (new_str);
    }
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
