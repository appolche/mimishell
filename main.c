#include "minishell.h"
/*
shlvl=.... обрубить по равно и поменть env
$?
*/

void check_list_splitted_cmd_redir(t_list *list)
{ // //проверка
    t_list *tmp = list;
    int k;
    while (tmp)
    {
        k = -1;
        if (tmp->cmd)
        {
        while (tmp->cmd[++k])
            printf("cmd: %d: %s\n", k, tmp->cmd[k]);
        }
        k = -1;
        if (tmp->redir)
        {
            while (tmp->redir[++k])
                printf("red: %d: %s\n", k, tmp->redir[k]);
        }
        tmp = tmp->next;
    }
}

void check_list_splitted_str(t_list *list)
{ // //проверка
    t_list *tmp = list;
    int k = 1;
    while (tmp)
    {
        printf("list->str: %d: |%s|\n", k, tmp->str);
        printf("list->str: %d: |%s|\n", k, tmp->str_cmd);
        printf("list->str_redir: %d: |%s|\n", k, tmp->str_redir);
        k++;
        tmp = tmp->next;
    }
}

int shell_loop(t_data *data, t_envp *envp)
{
    t_list  *list;

    while (1)
    {
        list = NULL;
        data->str = readline("minishell: ");
        if (data->str)
        {
            add_history(data->str);
            split_for_list(ft_strtrim(data->str, " "), &list);
        }
        if (list)
        {
            parse_list(envp, list);
            parse_each_node(list);
        }
        
        //pipe_cmd_proc(list, envp)
        //     ft_exit(1); //должен вывести новую строчку | сделать ошибку только выделения памяти
        // check_list_splitted_str(list);
        //check_list_splitted_cmd_redir(list);
        if (list)
            free_list(&list);
        if (data->str)
            free(data->str);
    }
    rl_clear_history();
}

int main(int argc, char **argv, char **env)
{
    t_data *data;
    t_envp *envp;

    data = malloc(sizeof(t_data));
    if (!data)
        return (0);

    if (env_copy(data, env) == 1)
        return (1);
    envp = NULL; 
    envp = init_t_envp(data, envp);
    if (!envp)
        exit(2);
        while(envp)
        {
            printf("%s\n", envp->name);
            envp=envp->next;
        }
    //shell_loop(data, envp);
    ft_lstclear(&envp);
    free_env(data);
    free(data);
    return (0);
}