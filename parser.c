#include "minishell.h"

void parse_each_node(t_list *list)
{
    while (list)
    {
        if (list->str_cmd)
            list->cmd = ft_split(list->str_cmd, ' ');
        list = list->next;
    }
}

int parse_list(t_envp *envp, t_list *list, t_data *data)
{
    int i;

    while (list)
    {
        //учесть ошибки в кавычках, должен пропускать
        if (syntax_errors(list->str) || redir_syntax_errors(list->str))
            return (0);
        list->str_cmd = ft_strtrim(list->str, " ");
        i = -1;
        while (list->str_cmd[++i])
        {
            if (list->str_cmd[i] == '\'')
                list->str_cmd = ft_single_quotes(list->str_cmd, &i);
            else if (list->str_cmd[i] == '\"')
                list->str_cmd = ft_double_quotes(list->str_cmd, &i, envp);
            if (list->str_cmd[i] == '$')
            {
                list->str_cmd = ft_dollar(list->str_cmd, &i, envp);
                if (list->str_cmd == NULL)
                    return (0);
            }
            if (list->str_cmd[i] == '>' || list->str_cmd[i] == '<')
            {
                list->str_cmd = split_cmd_redir(list, list->str_cmd, i);
                i--;
            }
        }
        if (list->str_redir)
            parse_redirect(list, list->str_redir, data);
        list = list->next;
    }
    return (1);
}

int split_for_list(char *str, t_list **list)
{
    int i;
    int j;

    i = -1;
    j = 0;
    while (str[++i])
    {
        if (str[i] == '\'')
        {
            if (check_unclosed_quotes(str, &i, '\''))
                return (0);
        }
        else if (str[i] == '\"')
        {
            if (check_unclosed_quotes(str, &i, '\"'))
                return (0);
        }
        if (str[i] == '|')
        {
            *list = create_list(*list, str, i, j);
            j = i;
        }
    }
    *list = create_list(*list, str, i, j);
    make_null_init(*list);
    free(str);
    return (1);
}