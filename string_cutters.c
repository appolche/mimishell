#include "minishell.h"

char *cut_cmd_piece(char *str, int start, int i, int size)
{
    char *tmp2;
    char *tmp3;
    char *new_str;

    tmp2 = ft_substr(str, 0, start);
    tmp3 = ft_substr(str, i, ft_strlen(str) - start - size);
    if (!tmp2 || !tmp3)
        return (NULL);
    new_str = ft_strjoin(tmp2, tmp3);
    if (!new_str)
        return (NULL);
    return (new_str);
}

char *split_cmd_redir(t_list *list, char *str, int i)
{
    int start;
    int len;
    char *tmp;
    char *new_str;

    start = i;
    i++;
    if (str[i] == '>' || str[i] == '<')
        i++;
    while (str[i] && str[i] == ' ')
        i++;
    while (str[i])
    {
        if (str[i] == ' ')
            break;
        i++;
    }
    tmp = ft_substr(str, start, i - start);
    if (!list->str_redir)
        list->str_redir = tmp;
    else
        list->str_redir = ft_strjoin(list->str_redir, tmp);
    new_str = cut_cmd_piece(str, start, i, ft_strlen(tmp));
    if (!new_str)
        return (NULL);
    free(str);
    return (new_str);
}

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

char *cut_quotes(char *str, int start, int end)
{
    char *tmp;
    char *tmp2;
    char *tmp3;

    tmp = ft_substr(str, 0, start);
    tmp2 = ft_substr(str, start + 1, end - start - 1);
    tmp3 = ft_substr(str, end + 1, ft_strlen(str) - end);
    if (!tmp || !tmp2 || !tmp3)
        return (NULL);
    tmp = ft_strjoin(tmp, tmp2);
    if (!tmp)
        return (NULL);
    tmp = ft_strjoin(tmp, tmp3);
    if (!tmp)
        return (NULL);
    return (tmp);
}