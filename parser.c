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

void parse_redirect(t_list *list)
{
    int i;
    char *file_name;

    i = -1;
    while (list)
    {
        while (list->str_redir[++i])
        {
            file_name = cut_file_name(list->str, i + 1, &i + 1);
            if (list->str_redir[i] == '<' && list->str_redir[i + 1] != '<') // read_only
                list->file_fd[0] = open(file_name, O_RDONLY);
            if (list->str_redir[i] == '>' && list->str_redir[i + 1] != '>') //rewrite
                list->file_fd[1] = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666); //отделить названия файлов от редиректов
            if (list->str_redir[i] == '<' && list->str_redir[i + 1] == '<') //heredoc
                heredoc_mode(); //add heredoc func
            if (list->str_redir[i] == '>' && list->str_redir[i + 1] == '>') //дозапись
                list->file_fd[1] = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
            free(file_name);
        }
    }
}


void parse_list(t_envp *envp, t_list *list)
{
    int i;

    while (list)
    {
        if (redir_syntax_errors(list->str))
            return;
        list->str_cmd = ft_strtrim(list->str, " ");
        i = -1;
        while (list->str_cmd[++i])
        {
            if (list->str_cmd[i] == '\'')
                list->str_cmd = ft_single_quotes(list->str_cmd, &i);
            else if (list->str_cmd[i] == '\"')
                list->str_cmd = ft_double_quotes(list->str_cmd, &i, envp);
            if (list->str_cmd[i] == '$')
                list->str_cmd = ft_dollar(list->str_cmd, &i, envp);
            if (list->str_cmd[i] == '>' || list->str_cmd[i] == '<')
            {
                list->str_cmd = split_cmd_redir(list, list->str_cmd, i);
                i--;
            }
        }
        list = list->next;
    }
}

void split_for_list(char *str, t_list **list)
{
    int i;
    int j;

    i = -1;
    j = 0;
    if (syntax_errors(str))
    {
        free(str);
        return;
    }
    while (str[++i])
    {
        if (str[i] == '\'')
        {
            if (check_unclosed_quotes(str, &i, '\''))
                return;
        }
        else if (str[i] == '\"')
        {
            if (check_unclosed_quotes(str, &i, '\"'))
                return;
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
}