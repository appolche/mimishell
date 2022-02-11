#include "minishell.h"

int ifkey(char c)
{
    if (c == '_' || ft_isalnum(c))
        return (1);
    return (0);
}

char *cut_char(char *str, int i, int j)
{
    char *tmp;
    char *tmp2;
    char *tmp3;

    //добавить проверки на ноль
    tmp = ft_substr(str, 0, j);
    tmp2 = ft_substr(str, j + 1, i - j - 1);
    tmp3 = ft_strdup(str + i + 1);
    tmp = ft_strjoin(tmp, tmp2);
    tmp = ft_strjoin(tmp, tmp3);
    return (tmp);
}

char    *ft_dollar(char *str, int *i, char **env)
{
    //сегается при "$USERhhh" и $USERhhh | баш при этом ничего не выводит (если нет другого арг)
    //мусор выводит, глупый
    //$? - обработать -  возвращает код последней отработавшей программы 
    //должен вылетать при вводе направильной переменной без одинарных кавычек (при двойных тодже вылетает)
    int j;
    int k;
    char *key;
    char *tmp2;
    int z;

    k = -1;
    j = *i;
    z = 0;
    while (str[++(*i)])
    {
        if (!ifkey(str[*i]))
            break;
    }
    if (*i == j + 1)
        return (str);
    key = ft_substr(str, j + 1, *i - j - 1);
    while (env[++k])
    {
        if (strstr(env[k], key)) //написать свой стрстр
		{
            z = 0;
            while (env[k][z] && env[k][z] != '=')
                z++;
            tmp2 = ft_substr(env[k], 0, z);
            if (strcmp(key, tmp2) == 0) //написать свой стркмп
                break;
		}
    }
    tmp2 = ft_substr(env[k], z + 1, strlen(env[k]) - z);
    //убрать $USER заменить на dleaves
    
    char *tmp;
    char *tmp3;

    tmp = ft_substr(str, 0, j);
    tmp3 = ft_substr(str, *i, *i - j);
    tmp = ft_strjoin(tmp, tmp2);
    tmp = ft_strjoin(tmp, tmp3);
    //добавить проверки на ноль
    free(key);
    free(str);
    return (tmp);

}

char *ft_backslash(char *str, int *i)
{
    char *tmp;
    char *tmp2;

    tmp = ft_substr(str, 0, *i);
    tmp2 = ft_strdup(str + *i + 1);
    tmp = ft_strjoin(tmp, tmp2);
    free(str);
    ++(*i);
    return (tmp);
}

char *ft_double_quotes(char *str, int *i, char **env)
{
    int j;
    char *str_new;

    j = *i;
    while (str[++(*i)])
    {
        if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '\\' || str[*i + 1] == '$'))
            str = ft_backslash(str, i);
        if (str[*i] == '$')
            str = ft_dollar(str, i, env);
        if (str[*i] == '\"')
            break;
    }
    str_new = cut_char(str, *i, j);
    free(str);
    return (str_new);
}

char *ft_quotes(char *str, int *i)
{
    int j;
    char *str_new;

    j = *i;
    if (str[*i + 1] == '\'')
        return(str);
    while (str[++(*i)])
    {
        if (str[*i] == '\'')
            break;
    }
    str_new = cut_char(str, *i, j);
    free(str);
    return (str_new);
}

int lexer_errors(char *str)
{
    int i;

    i = -1;
    while(str[++i])
    {
        if (str[0] == '|' || str[0] == ';')
        {
            printf("minishell: syntax error near unexpected token `%c'\n", str[0]);
            return (1);
        }
        else if ((str[i] == ';' || str[i] == '|') && (str[i + 1] == ';' || str[i + 1] == '|'))
        {
            printf("minishell: syntax error near unexpected token `%c'\n", str[i + 1]);
            return (1);
        }
    }
    return (0);
}

char *lexer(char *rl_str, char **env)
{
    int i;
    char *str;

    i = -1;
    str = ft_strtrim(rl_str, " ");
    //добавить защиту на не закрытые ковычки и др ошибки
    if (lexer_errors(str))
        return (NULL);
    while(str[++i])
    {
        if (str[i] == '\'')
            str = ft_quotes(str, &i);
        if (str[i] == '\"')
            str = ft_double_quotes(str, &i, env);
        if (str[i] == '\\')
            str = ft_backslash(str, &i);
        if (str[i] == '$')
            str = ft_dollar(str, &i, env);
    }
    return (str);
}

// if (| || < || >> || >)


// minishell: "$USER"
// dleaves
// minishell: "\\ $USER hhh '' \' "
// minishell: "\\ $USER hhh '' \' "
// minishell: "\\ USER hhh '' \' "
// \ dleaves hhh \ dleaves hhh \ USER hhh '' \' 