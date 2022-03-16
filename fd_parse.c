#include "minishell.h"

// minishell: ls > "  fddddd   file1" > "   file2678" > "  |  file3   jj<>"
//  minishell: error: unclosed double quotes
//  minishell: ls > file1| <<file2<file3<file4 cat
//  minishell: syntax error near unexpected token `<<'
//  сделать обработку доллара в редиректе (раскрывает значение перемеенной и делает его filename)

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

void open_file(t_list *list, char *redir_type, char *file_name, t_data *data)
{
    int j;

    j = 0;
    if (redir_type[j] == '>')
    {
        if (list->file_fd[1] != -1 || list->file_fd[1] != -2)
            close(list->file_fd[1]);
        if (redir_type[j + 1] == '>')
        {
            list->file_fd[1] = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
            if (list->file_fd[1] == -1)
                printf("minishell: %s: Permission denied\n", file_name);
        }
        else
            list->file_fd[1] = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    }
    else if (redir_type[j] == '<')
    {
        if (list->file_fd[0] != -1 || list->file_fd[0] != -2)
            close(list->file_fd[0]);
        if (redir_type[j + 1] == '<')
            list->file_fd[0] = here_doc_mode(file_name, data);
        else if (redir_type[j + 1] == '>')
            printf("minishell: syntax error near unexpected token `newline'\n");
        else
        {
            list->file_fd[0] = open(file_name, O_RDONLY);
            if (list->file_fd[0] == -1)
            {
                // data.exit_status = 1;
                printf("minishell: %s: No such file or directory\n", file_name);
            }
        }
    }
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
                break;
            i++;
        }
        file_name = ft_substr(str, start, i - start);
    }
    *ret = i;
    return (file_name);
}

void parse_redirect(t_list *list, char *str_redir, t_data *data)
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
        file_name = get_file_name(str, i, &i);
        open_file(list, redir_type, file_name, data);
    }
    free(str);
    str = NULL;
}