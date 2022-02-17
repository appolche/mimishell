#include "minishell.h"

void parse_each_node(t_list *list)
{
    while (list)
    {
        if (list->str_cmd)
            list->cmd = ft_split(list->str_cmd, ' ');
        if (list->str_redir)
            list->redir = ft_split(list->str_redir, ' ');
        list = list->next;
    }
}
// shlvl=.... обрубить по равно и поменть env

void cut_str_cmd(t_list *list, int start)
{
    //запомнить до и запомнить после и стрджоин
    char *tmp;
    char *tmp2;
    char *tmp3;
    int len = 0;
    int redir_len = 0;

    if (!ft_strchr(list->str, '>') && !ft_strchr(list->str, '<'))
    {
        list->str_cmd = ft_strdup(list->str);
        list->str_redir = NULL;
    }
    else
    {
        redir_len = ft_strlen(list->str_redir); //меньше чем в изначальной строке
        len = ft_strlen(list->str);
        tmp = ft_substr(list->str, 0, start);
        tmp2 = ft_substr(list->str, start + redir_len, len - redir_len);
        list->str_cmd = ft_strjoin(tmp, tmp2);
    }
    printf("str_cmd: %s\n", list->str_cmd);
}

// char *cut_piece(char *str, int start/j, int end/i)
// {
//     char *tmp;
//     char *tmp2;
//     int  size;

//     tmp = ft_substr(str, 0, start);
//     //tmp2 = ft_strdup(value);
//     tmp2 = ft_substr(str, start + size, ft_strlen(str) - start);
//     if (!tmp || !tmp2)
//         return (NULL);
//     tmp = ft_strjoin(tmp, tmp2);
//     if (!tmp)
//         return (NULL);
//     free(str);
//     return (tmp);
// }
//new_str = cut_and_change_piece(str, start, tmp->name, tmp->value);

void redir_copy(t_list *list, char *str, int i, int j)
{
    int start;
    int len;
    char *tmp;

    if (!str)
        return ;
    start = i;
    i++;
    while (str[i] && str[i] == ' ')
        i++;
    while (str[i])
    {
        if (str[i] == ' ')
            break;
        i++;
    }
    tmp = ft_substr(str, start, i - start);
    if (!list->str_redir)
        list->str_redir = tmp;
    else
        list->str_redir = ft_strjoin(list->str_redir, tmp);
}

int check_redirs(t_list *list)
{
    int i;
    int count;
    int j;

    while (list)
    {
        i = -1;
        j = 0;
        while (list->str[++i])
        {
            if (list->str[i] == '>' || list->str[i] == '<') //затирает и перезаписывает в файл
            {
                redir_copy(list, list->str, i, j);
                j = i;
            }
        }
        printf("str_redir: %s\n", list->str_redir);
        //cut_str_cmd(list, j);
        list = list->next;
    }
    return (0);
}

int trim_list_strs(t_list *list)
{
    char *tmp;

    while (list)
    {
        tmp = ft_strtrim(list->str, " ");
        if (!tmp)
            return (1);
        free(list->str);
        list->str = tmp;
        list = list->next;
    }
    return (0);
}

void list_parse(t_list *list, t_data *data) // change to data->str
{
    if (trim_list_strs(list))
        ft_exit(1);
    if (check_redirs(list))
        ft_exit(1);
    // parse_each_node(list);
    // return (list);
}