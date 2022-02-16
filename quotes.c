#include "minishell.h"

int check_unclosed_quotes(int quote_pair, char *str)
{
    if (quote_pair == 0)
    {
        free(str);
        printf("minishell: error: unclosed double quotes\n");
        return (1);
    }
    else
        return (0);
}

// char *check_pipes_in_quotes(char *str)
// {
//     int pipe_in_quotes;
//     int i;

//     pipe_in_quotes = 0;
//     i = 0;
//     while (str[i++])
//     {
//         if (str[i] == '|')
//             pipe_in_quotes++;
//     }
//     if (pipe_in_quotes)
//     {
// заменить пайп на что-то другое, потом вернуть на место после сплита...........
//     }
   
// }

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
    int flag = 0;

    tmp = ft_substr(str, 0, start);
    tmp2 = ft_substr(str, start + 1, end - start - 1); //проверка на пайп внутри кавычек
    //tmp2 = check_pipes_in_quotes(tmp2);
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

char    *ft_single_quotes(char *str, int *i) //добавить проверку на нечетные кавычки
{
    char    *str_new;
    int     start;
    int     quote_pair;

    start = *i;
    quote_pair = 0;
    while (str[++(*i)])
    {
        if (str[*i] == '\'')
        {
            quote_pair++;
            break;
        }
    }
    if (check_unclosed_quotes(quote_pair, str))
        return (NULL);
    str_new = cut_quotes(str, start, *i);
    if (!str_new)
        return (NULL);
    free(str);
    (*i) -= 2;
    return (str_new);
}

char    *ft_double_quotes(char *str, int *i, t_envp *envp)
{
    char    *str_new;
    int     start;
    int     quote_pair;

    start = *i;
    quote_pair = 0;
    while (str[++(*i)])
    {
        if (str[*i] == '$')
        {
            str = ft_dollar(str, i, envp);
            if (!str)
                return (NULL);
        }
        if (str[*i] == '\"')
        {
            quote_pair++;
            break;
        }
    }
    if (check_unclosed_quotes(quote_pair, str))
        return (NULL);
    str_new = cut_quotes(str, start, *i);
    if (!str_new)
        return (NULL);
    free(str);
    (*i) -= 2;
    return (str_new);
}