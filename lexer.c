#include "minishell.h"

//$?  echo "|" 
//обработать нули на выходе

static int lexer_errors(char *str)
{
    int i;

    i = -1;
    while (str[++i])
    {
        if (str[0] == '|')
        {
            printf("minishell: syntax error near unexpected token `|'\n");
            return (1);
        }
        else if (str[i] == '|' && str[i + 1] == '\0')
        {
            printf("minishell: error: no command after pipe\n");
            return (1);
        }
    }
    return (0);
}

char *lexer(char *rl_str, t_envp *envp, t_list **list)
{
    char *str;
    int i;
    int j;

    i = -1;
    j = 0;
    str = ft_strtrim(rl_str, " "); //cut spaces
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
        if (str[i] == '|')
        {
            *list = create_list(*list, str, i, j);
            if (!str)
                break;
            j = i;
        }
    }
    *list = create_list(*list, str, i, j);
    make_null_init(*list);
    return (str);
}