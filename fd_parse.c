#include "minishell.h"

void redirect_fd(t_list *list)
{
    if (list->file_fd[0] >= 0)
    {
        dup2(list->file_fd[0], 0);
        close(list->file_fd[0]);
    }
    else if (list->file_fd[0] == -1)
    {
        printf("minishell: Permission denied\n");
        exit(1);
    }
    if (list->file_fd[1] >= 0)
    {
        dup2(list->file_fd[1], 1);
        close(list->file_fd[1]);
    }
    else if (list->file_fd[1] == -1)
    {
        printf("minishell: Permission denied\n");
        exit(1);
    }
}

void open_input_fd(t_list *list, char *redir_type, char *file_name)
{
    if (list->file_fd[0] != -1 || list->file_fd[0] != -2)
        close(list->file_fd[0]);
    if (redir_type[1] == '<')
        list->file_fd[0] = here_doc_mode(file_name);
    else if (redir_type[1] == '>')
        printf("minishell: syntax error near unexpected token `newline'\n");
    else
    {
        list->file_fd[0] = open(file_name, O_RDONLY);
        if (list->file_fd[0] == -1)
            data.exit_status = 1;
    }
}

void open_output_fd(t_list *list, char *redir_type, char *file_name)
{
    if (list->file_fd[1] != -1 || list->file_fd[1] != -2)
        close(list->file_fd[1]);
    if (redir_type[1] == '>')
    {
        list->file_fd[1] = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
        if (list->file_fd[1] == -1)
            data.exit_status = 1;
    }
    else
        list->file_fd[1] = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
}

void open_file(t_list *list, char *redir_type, char *file_name)
{
    if (redir_type[0] == '>')
        open_output_fd(list, redir_type, file_name);
    else if (redir_type[0] == '<')
        open_input_fd(list, redir_type, file_name);
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
        open_file(list, redir_type, file_name);
    }
    free(str);
    str = NULL;
}