#include "minishell.h"

int check_unclosed_quotes(char *str, int *i, int c)
{
    int     quote_pair;

    quote_pair = 0;
    while (str[++(*i)])
    {
        if (str[*i] == c)
        {
            quote_pair++;
            break;
        }
    }
    if (quote_pair == 0)
    {
        free(str);
        printf("minishell: error: unclosed double quotes\n");
        return (1);
    }
    else
        return (0);
}

char    *ft_double_quotes(char *str, int *i, t_envp *envp)
{
    char    *str_new;
    int     start;

    start = *i;
    // if (check_unclosed_quotes(str, i, '\"'))
    //     return (NULL);
    while (str[++(*i)])
    {
        if (str[*i] == '$')
        {
            str = ft_dollar(str, i, envp);
            if (!str)
                return (NULL);
        }
        if (str[*i] == '\"')
            break;
    }
    str_new = cut_quotes(str, start, *i);
    if (!str_new)
        return (NULL);
    free(str);
    (*i) -= 2;
    return (str_new);
}

char    *ft_single_quotes(char *str, int *i) //добавить проверку на нечетные кавычки
{
    char    *str_new;
    int     start;

    start = *i;
    if (check_unclosed_quotes(str, &(*i), '\''))
        return (NULL);
    str_new = cut_quotes(str, start, *i);
    if (!str_new)
        return (NULL);
    free(str);
    (*i) -= 2;
    return (str_new);
}
