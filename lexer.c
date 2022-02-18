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

char *ft_redirect(char *str, int *i, char *redir)
{
    int start;
    int len;
    char *tmp;

    if (!str)
        return (NULL);
    start = *i;
    *i++;
    while (str[*i] && str[*i] == ' ')
        *i++;
    while (str[*i])
    {
        if (str[*i] == ' ')
            break;
        *i++;
    }
    tmp = ft_substr(str, start, *i - start);
    if (!redir)
        redir = tmp;
    else
        redir = ft_strjoin(redir, tmp);
    return (redir);
}

int pre_lexer(char *rl_str, t_list **list)
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
        return (1);
    }
    while (str[++i])
    {
        if (str[i] == '\'')
        {
            if (check_unclosed_quotes(str, &i, '\''))
                return (1);
        }
        else if (str[i] == '\"')
        {
            if (check_unclosed_quotes(str, &i, '\"'))
                return (1);
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
    free (str);
    return (0);
}
//дописать разделение кмд и рдр

void lexer(char *rl_str, t_envp *envp, t_list *list)
{
    int i;
    int j;

    i = -1;
    j = 0;
    while (list)
    {
        while (list->str[++i])
        {
            if (list->str[i] == '\'')
            {
                list->str = ft_single_quotes(list->str, &i);
                if (!list->str)
                    break;
            }
            else if (list->str[i] == '\"')
            {
                list->str = ft_double_quotes(list->str, &i, envp);
                if (!list->str)
                    break;
            }
            if (list->str[i] == '$')
            {
                list->str = ft_dollar(list->str, &i, envp);
                if (!list->str)
                    break;
            }
            if (list->str[i] == '>' || list->str[i] == '<')
                list->str_redir = ft_redirect(list->str, &i, list->str_redir);
        }
        list = list->next;
    }

}