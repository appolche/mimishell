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


//minishell: ls > "  fddddd   file1" > "   file2678" > "  |  file3   jj<>"
// minishell: error: unclosed double quotes
// minishell: ls > file1| <<file2<file3<file4 cat
// minishell: syntax error near unexpected token `<<'
// сделать обработку доллара в редиректе (раскрывает значение перемеенной и делает его filename)
char *get_file_name(char *str, int i)
{
    // <
    char *file_name;
    int start;
    int quote_start;

    while (str[i] && (str[i] == ' ' || str[i] == '>' || str[i] == '<')) // rewrite
        i++;
    start = i;
    // if (str[i] == '\'')
    // {
    //     quote_start = i;
    //     check_unclosed_quotes(str, &i, '\'');
    //     file_name = ft_substr(str, quote_start + 1, i - quote_start - 1);
    // }
    // else if (str[i] == '\"')
    // {   
    //     quote_start = i;
    //     check_unclosed_quotes(str, &i, '\"');
    //     file_name = ft_substr(str, quote_start + 1, i - quote_start - 1);
    // }
    // else
    // {
        while (str[i])
        {
            if (str[i] == ' ' || str[i] == '>' || str[i] == '<')
                break ;
            
            (i)++;
        }
        file_name = ft_substr(str, start, i - start);
    // }
    return (file_name);
}

void parse_redirect(t_list *list)
{
    int i;
    char *file_name;

    file_name = NULL;
    while (list)
    {
        i = -1;
        while (list->str_redir[++i])
        {
            if (list->str_redir[i] == '<' && list->str_redir[i + 1] != '<') // read_only
            {
                file_name = get_file_name(list->str_redir, i);
                printf ("filename: |%s| \n", file_name);
                i += ft_strlen(file_name);
                // list->file_fd[0] = open(file_name, O_RDONLY);
            }
            if (list->str_redir[i] == '>' && list->str_redir[i + 1] != '>') // rewrite
            {
                file_name = get_file_name(list->str_redir, i);
                printf ("filename: |%s| \n", file_name);
                i += ft_strlen(file_name);
                // list->file_fd[1] = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666); //отделить названия файлов от редиректов
            }
            if (list->str_redir[i] == '<' && list->str_redir[i + 1] == '<') // heredoc
            {
                file_name = get_file_name(list->str_redir, i);
                printf ("filename: |%s| \n", file_name);
                i += ft_strlen(file_name);
                // heredoc_mode(); // add heredoc func // стоп-слово сразу после редира
            }
            if (list->str_redir[i] == '>' && list->str_redir[i + 1] == '>') //дозапись
            {
                file_name = get_file_name(list->str_redir, i);
                printf ("filename: |%s| \n", file_name);
                i += ft_strlen(file_name);
                // list->file_fd[1] = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
            }
            if (file_name)
            {
                free(file_name);
                file_name = NULL;
            }
        }
        list = list->next;
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