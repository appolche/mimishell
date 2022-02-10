#include "minishell.h"

//pwd | ls -la > file1 | 

void parse_each_node(t_list *list)
{
    int i;

    while (list)
    {
        if (list->str_cmd)
            list->cmd = ft_split(list->str_cmd, ' ');
        if (list->str_redir)
            list->redir = ft_split(list->str_redir, ' ');
        list = list->next;
    }
}

char    *ft_substr_cpy(char *src, int start, char c)
{
    char *dst;
	int	i;
	int	len;

	if (!src)
		return (0);
	i = start + 1;
    if (src[i] == c)
    {
	    while (src[i] == c)
		    i++;
    }
    while (src[i] != c)
		    i++;
    len = i - start;
    dst = ft_substr(src, start, len);
	return (dst);
}
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
        redir_len = ft_strlen(list->str_redir);
        len = ft_strlen(list->str);
        tmp = ft_substr(list->str, 0, start);
        tmp2 = ft_substr(list->str, start + redir_len, len - redir_len);
        list->str_cmd = ft_strjoin(tmp, tmp2);
        free(tmp);
        free(tmp2);
    }
    printf("%s\n", list->str_cmd);
}

int check_redirs(char *str, t_list *list)
{
    int i;
    int n;
    int start;

    while(list)
    {
        i = -1;
        n = 0;
        start = 0;
        list->str_redir = NULL;
        list->str_cmd = NULL;
        while (list->str[++i])
        {
            if (list->str[i] == '>' || list->str[i] == '<') //затирает и перезаписывает в файл
            {
                if (n == 0)
                { 
                    start = i;
                    list->str_redir = ft_substr_cpy(str, i, ' ');
                    if (!list->str_redir)
                        return (1);
                }
                else
                {
                    //мб добавить пробел между строками
                    list->str_redir = ft_strjoin(list->str_redir, ft_substr_cpy(str, i, ' '));
                    if (!list->str_redir)
                        return (1);
                }
                n++;
                printf("%s\n", list->str_redir);
            }
        }
        cut_str_cmd(list, start);
        list = list->next;
    }
    return (0);
}

// if (| || < || >> || >)

int shell_loop(t_data *data, char **argv)
{
    t_list *list;
    char *str;

    while (1)
    {
        list = NULL;
        str = readline("minishell: ");
        if (str)
            add_history(str);
        else if (str == NULL)
        {
            ft_putstr_fd("exit\n", 1);
            return (1);
        }
        printf("%s\n", str);
        // data->str = lexer(str, data->env);
        // if (!data->str)
        //     exit(1); //сделать ретурн?
        // list = list_cmds(&list, data->str);
        // if (check_redirs(data->str, list))
        //     exit(1);
        // parse_each_node(list);
        //one_cmd_proc(list->cmd, data->env);
        //pipe_cmd_proc(list, data->env);

        //проверка
        // t_list *tmp = list;
        // int k;
        // while (tmp)
        // {
        //     k = -1;
        //     while (tmp->cmd[++k])
        //         printf("cmd: %d: %s\n", k, tmp->cmd[k]);
        //     k = -1;
        //     while (tmp->redir[++k])
        //         printf("red: %d: %s\n",k, tmp->redir[k]);
        //     tmp = tmp->next;
        // }
        // free(data->str);
        //free(list->str_cmd);
        // free(list->str_redir);
        // free(list);
    }
}

int main(int argc, char **argv, char **env)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    if (env_copy(data, env) == 1)
    {
        free(data);
        return (1);
    }
    shell_loop(data, argv);
    free_env(data);
    free(data);
    return (0);
}
