#include "minishell.h"

//$?  echo "|" 
//обработать нули на выходе

static int lexer_errors(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (str[i] == '|' && str[i + 1] == '\0')
        {
            printf("minishell: error: no command after pipe\n");
            return (1);
        }
    }
    return (0);
}

char    *ft_dollar(char *str, int *i, t_envp *envp)
{
    //сегается при "$USERhhh" и $USERhhh | баш при этом ничего не выводит (если нет другого арг)
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
    printf("%s\n", name);
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

char *lexer(char *rl_str, t_envp *envp)
{
    char *str;
    int i;

    i = -1;
    str = ft_strtrim(rl_str, " ");
    if (lexer_errors(str))
    {   
        free(str);
        return (NULL);
    }
    while (str[++i])
    {
        if (str[i] == '\'')
        {
            str = ft_single_quotes(str, &i);
            if (!str)
                break;
        }
        else if (str[i] == '\"')
        {
            str = ft_double_quotes(str, &i, envp);
            if (!str)
                break;
        }
        if (str[i] == '$')
        {
            str = ft_dollar(str, &i, envp);
            if (!str)
                break;
        }
    }
    printf("|%s|\n", str);
    return (str);
}