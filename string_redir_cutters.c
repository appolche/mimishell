#include "minishell.h"

char *filename_in_quotes(char *str, int *i, int c)
{
    char *file_name;
    int quote_start;

    quote_start = *i;
    while (str[++(*i)])
    {
        if (str[*i] == c)
            break;
    }
    file_name = ft_substr(str, quote_start + 1, *i - quote_start - 1);
    return (file_name);
}

char *get_file_name(char *str, int i, int *ret)
{
    char *file_name;
    int start;
    int quote_start;

    while (str[i] && str[i] == ' ')
        i++;
    start = i;
    if (str[i] == '\'')
        file_name = filename_in_quotes(str, &i, '\'');
    else if (str[i] == '\"')
        file_name = filename_in_quotes(str, &i, '\"');
    else
    {
        while (str[i])
        {
            if (str[i] == ' ' || str[i] == '>' || str[i] == '<' || str[i] == '\'' || str[i] == '\"')
                break;
            i++;
        }
        file_name = ft_substr(str, start, i - start);
    }
    *ret = i;
    return (file_name);
}