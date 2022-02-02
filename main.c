#include "minishell.h"

void parse_each_node(t_list *list)
{
    int i;

    while (list)
    {
        list->cmd = ft_split(list->str, ' ');
        list = list->next;
    }
}

// if (| || < || >> || >)

t_list *list_cmds(t_list **list, char *str)
{
    int i = -1;
    int j = 0;

    while (str[++i])
    {
        if (str[i] == '|')
        {
            if (!*list)
            {
                j = i;
                *list = create_list(ft_substr(str, 0, i));
            }
            else
            {
                ft_push_back(*list, ft_substr(str, j + 1, i - j - 1));
                j = i;
            }
        }
    }
    if (str[i] == '\0')
    {
        if (!*list)
            *list = create_list(ft_substr(str, 0, i));
        else
            ft_push_back(*list, ft_substr(str, j + 1, i - j - 1));
    }
    return (*list);
}

int shell_loop(t_data *data, char **argv)
{
    t_list *list;
    char *str;

    while (1)
    {
        t_list *list = NULL;
        write(1, "minishell: ", 11);
        data->str = gnl_stdin(0);
        if (data->str == NULL)
        {
            ft_putstr_fd("exit\n", 1);
            return (1);
        }
        str = lexer(data->str, data->env);
        if (!str)
            exit(1); //сделать ретурн?
        printf("%s\n", str);
        list = list_cmds(&list, str);
        parse_each_node(list);
        //one_cmd_proc(list->cmd, data->env);
        pipe_cmd_proc(list, data->env);

        //проверка
        // t_list *tmp = list;
        // int c = -1;
        // while (tmp)
        // {
        //     c = -1;
        //     while (tmp->cmd[++c] != NULL)
        //         printf("%d: %s\n",c, tmp->cmd[c]);
        //     tmp = tmp->next;
        // }

        free(list);
    }
}

int main(int argc, char **argv, char **env)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    // env copy
    if (env_copy(data, env) == 1)
        return (1);
    shell_loop(data, argv);
    free_env(data);
    free(data);
    return (0);
}