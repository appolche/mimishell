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

char *filename_in_quotes(char *str, int *i, int c)
{
    char *file_name;
    int quote_start;

    quote_start = *i;
    while (str[++(*i)])
    {
        if (str[*i] == c)
            break;
    }
    file_name = ft_substr(str, quote_start + 1, *i - quote_start - 1);
    return (file_name);
}

char *get_file_name(char *str, int i, int *ret)
{
    char *file_name;
    int start;
    int quote_start;

    while (str[i] && str[i] == ' ')
        i++;
    start = i;
    if (str[i] == '\'')
        file_name = filename_in_quotes(str, &i, '\'');
    else if (str[i] == '\"')
        file_name = filename_in_quotes(str, &i, '\"');
    else
    {
        while (str[i])
        {
            if (str[i] == ' ' || str[i] == '>' || str[i] == '<' || str[i] == '\'' || str[i] == '\"')
                break ;
            i++;
        }
        file_name = ft_substr(str, start, i - start);
    }
    *ret = i;
    return (file_name);
}

/*
идем по строке
встречаем <> (проверяем кавычки, только пропуская содержимое)
запоминаем вид редиректа
запоминаем имя
отправляем имя и вид редиректа на исполнение
записываем открытый фд в лист
идем дальше по строке
если встречаем новый редирект, то закрываем старый фд и перезаписываем fd
*/



void open_file(t_list *list, char *redir_type, char *file_name)
{
    int j;

    j = 0;
    
    
    if (redir_type[j] == '>') 
    {   
        if (list->file_fd[1] != -1)
            close(list->file_fd[1]);    
        if (redir_type[j + 1] == '>') //дозапись
            list->file_fd[1] = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
        else // rewrite
            list->file_fd[1] = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    }
    else if (redir_type[j] == '<') 
    {
        if (list->file_fd[0] != -1)
            close(list->file_fd[0]);
        if (redir_type[j + 1] == '<') // heredoc
            list->file_fd[0] = here_doc_mode(file_name);
        else // read_only
        {
            list->file_fd[0] = open(file_name, O_RDONLY);
            if (list->file_fd[0] == -1)
                printf("minishell: %s: No such file or directory\n", file_name);
        }
    }
    //добавить проверки на open
    if (redir_type)
    {
        free(redir_type);
        redir_type = NULL;
    }
    if (file_name)
    {
        free(file_name);
        file_name = NULL;
    }
}

void parse_redirect(t_list *list, char *str_redir)
{
    int i;
    int j;
    int count;
    char *str;
    char *file_name;
    char *redir_type;

    file_name = NULL;
    redir_type = NULL;
    str = NULL;
    i = 0;
    j = 0;
    str = ft_strtrim(str_redir, " ");
    // printf("str: %s\n", str);
    //обработать несколько редиректов в одой строке (если str одной галкой не кончается) и зафришить стр не забыть
    while (str[i])
    {
        count = 0;
        j = i;
        while (str[i] && (str[i] == '<' || str[i] == '>'))
        {
            i++;
            count++;
        }
        redir_type = ft_substr(str, j, count);
    // printf("redir_type: %s\n", redir_type);
        file_name = get_file_name(str, i, &i);
    // printf("file_name: %s\n", file_name);
        open_file(list, redir_type, file_name);
    }
    free(str);
    str = NULL;
}

void parse_list(t_envp *envp, t_list *list)
{
    int i;

    while (list)
    {
        if (redir_syntax_errors(list->str))
            return ;
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
        parse_redirect(list, list->str_redir);
        list = list->next;
    }
}

void split_for_list(char *str, t_list **list)
{
    int i;
    int j;

    i = -1;
    j = 0;
    // if (syntax_errors(str))
    // {
    //     free(str);
    //     return;
    // }
    while (str[++i])
    {
        if (str[i] == '\'')
        {
            if (check_unclosed_quotes(str, &i, '\''))
                return ;
        }
        else if (str[i] == '\"')
        {
            if (check_unclosed_quotes(str, &i, '\"'))
                return ;
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