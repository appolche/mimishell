char *ft_backslash(char *str, int *i)
{
    char *tmp;
    char *tmp2;
    int slash_count;
    int start;

    // if (str[*i + 1] == '\\')
    //     return (str);
    slash_count = 1;
    start = *i;
    while (str[start])
    {
        start++;
        if (str[start] != '\\')
            break;
        slash_count++;

    }
     printf("|%d|\n", slash_count);
    if (slash_count % 2)
    {
        tmp = ft_substr(str, 0, start);
        tmp2 = ft_substr(str, start + (slash_count / 2), ft_strlen(str) - start - 1);
        if (!tmp || !tmp2)
            return (NULL);
        tmp = ft_strjoin(tmp, tmp2);
        if (!tmp)
            return (NULL);
        free(str);
        // ++(*i);
        *i = *i + slash_count / 2;
    }
    else
    {
        if (slash_count == 1)
        {
            tmp = ft_substr(str, 0, start);
            tmp2 = ft_substr(str, start + 1, ft_strlen(str) - start);
            if (!tmp || !tmp2)
                return (NULL);
            tmp = ft_strjoin(tmp, tmp2);
            if (!tmp)
                return (NULL);
            free(str);
            //++(*i);
        }
        else
        {
            tmp = ft_substr(str, 0, start);
            tmp2 = ft_substr(str, start, ft_strlen(str) - start + 1);
            if (!tmp || !tmp2)
                return (NULL);
            tmp = ft_strjoin(tmp, tmp2);
            if (!tmp)
                return (NULL);
            free(str);
            //++(*i);
        }
    }
    return (tmp);
}

char *lexer(char *rl_str, char **env)
{
    char *str;
    int i;

    i = -1;
    str = ft_strtrim(rl_str, " ");
    //добавить защиту на не закрытые ковычки и др ошибки
    if (lexer_errors(str))
        return (NULL);
    while (str[++i])
    {
        if (str[i] == '\'')
            str = ft_single_quotes(str, &i);
        // if (str[i] == '\"')
        //     str = ft_double_quotes(str, &i, env);
        if (str[i] == '\\')
            str = ft_backslash(str, &i);
        // if (str[i] == '$')
        //     str = ft_dollar(str, &i, env);
    }
    printf("|%s|\n", str);
    return (str);
}