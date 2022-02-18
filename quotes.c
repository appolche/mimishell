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

char *cut_quotes(char *str, int start, int end)
{
    char *tmp;
    char *tmp2;
    char *tmp3;
    int flag = 0;

    tmp = ft_substr(str, 0, start);
    tmp2 = ft_substr(str, start + 1, end - start - 1); //проверка на пайп внутри кавычек
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


char    *ft_double_quotes(char *str, int *i, t_envp *envp)
{
    char    *str_new;
    int     start;

    start = *i;
    while (str[++(*i)])
    {
        if (str[*i] == '$')
        {
            str = ft_dollar(str, i, envp);
            if (!str)
                return (NULL);
        }
    }
    // if (check_unclosed_quotes(str, *i, '\"'))
    //     return (NULL);
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
    // if (check_unclosed_quotes(str, *i, '\''))
    //     return (NULL);
    str_new = cut_quotes(str, start, *i);
    if (!str_new)
        return (NULL);
    free(str);
    (*i) -= 2;
    return (str_new);
}
