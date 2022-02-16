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
//shlvl=.... обрубить по равно и поменть env


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

char    *ft_substr_cpy(char *src, int *start, char c)
{
    char *dst;
	int	i;
	int	len;

	if (!src)
		return (0);
	i = *start + 1;
	while (src[i] && src[i] == c)
		    i++;
    while (src[i]) //до ближайшего пробела
    {
        if (src[i] == c)
            break;
        i++;
    }
    len = i - *start;
    dst = ft_substr(src, *start, len);
    *start = i - 1;
	return (dst);
}

int check_redirs(char *str, t_list *list)
{
    int i;
    int count;
    int start;

    while (list)
    {
        i = -1;
        count = 0;
        start = 0;
        while (list->str[++i])
        {
            if (list->str[i] == '>' || list->str[i] == '<') //затирает и перезаписывает в файл
            {
                if (count == 0)
                { 
                    start = i;
                    list->str_redir = ft_substr_cpy(str, &i, ' ');
                    count++;
                }
                else
                    list->str_redir = ft_strjoin(list->str_redir, ft_substr_cpy(str, &i, ' '));
                //мб добавить пробел между строками
            }
        }
        cut_str_cmd(list, start);
        printf("str_redir: %s\n", list->str_redir);
        list = list->next;
    }
    return (0);
}

int    trim_list_strs(t_list *list)
{
    char    *tmp;

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

void make_null_init(t_list *list)
{
    while (list)
    {
        list->str_cmd = NULL;
        list->str_redir = NULL;
        list->cmd = NULL;
        list->redir = NULL;
        list = list->next;
    }
}

t_list  *list_init(t_list *list, t_data *data) //change to data->str
{
    list = create_list(list, data->str);
    make_null_init(list);
    if (trim_list_strs(list))
        ft_exit(1); 
    if (check_redirs(data->str, list))
        ft_exit(1);
    parse_each_node(list);
    return (list);
}