#include "minishell.h"
/*
shlvl=.... обрубить по равно и поменть env
$?
*/

// bash-3.2$ USER=abc
// bash-3.2$ env | grep USER
// USER=abc

int shell_loop(t_data *data, t_envp *envp)
{
    t_list *list;

    while (1)
    {
        list = NULL;
        rl_on_new_line();
        data->str = readline("minishell: ");
        if (!data->str)
            exit(1);
        if (ft_strlen(data->str))
        {
            add_history(data->str);
            split_for_list(ft_strtrim(data->str, " "), &list);
        }
        if (list)
        {
            if (parse_list(envp, list, data))
            {
                parse_each_node(list);
                pipe_cmd_proc(list, envp, data);
            }
        }
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
    init_t_envp(data, &envp);
    if (!envp)
        exit(2);
    sig_init(data);
    ft_shlvl(envp);
    shell_loop(data, envp);
    ft_lstclear(&envp);
    free_env(data);
    free(data);
    return (0);
}