#include "../minishell.h"

//без аргв в пайпах работает
// с аргв не работает в пайпах

int ft_isdigit_char(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    else
        return (0);
}

void print_export(t_envp *list)
{
    while (list)
    {
        if (list->value == NULL)
            printf("declare -x %s=\"\"\n", list->name);
        else
            printf("declare -x %s=\"%s\" \n", list->name, list->value);
        list = list->next;
    }
}

t_envp *export_new_name(t_envp *envp, char *name)
{
    char **tmp;
    int check;
    int i;

    i = 0;
    tmp = (char **)malloc(sizeof(char *) * 2);
    check = ft_strchr(name, '=');
    if (check == 0)
    {
        tmp[0] = ft_strdup(name);
        tmp[1] = NULL;
    }
    else
    {
        free(tmp);
        tmp = ft_split(name, '=');
    }
    if (!tmp)
        exit(2);
    push_back(tmp[0], tmp[1], envp);
    envp = struct_head(envp);
    free(tmp);
    return (envp);
}

t_envp *copy_envp(t_envp *envp, t_envp *sort)
{
    t_envp *tmp;
    char *name;
    char *value;

    tmp = envp;
    sort = NULL;
    while (tmp)
    {
        name = ft_strdup(tmp->name);
        if (tmp->value == NULL)
            value = NULL;
        else
            value = ft_strdup(tmp->value);
        if (!sort)
            sort = ft_lstnew(name, value);
        else
            push_back(name, value, sort);
        tmp = tmp->next;
    }
    sort = struct_head(sort);
    return (sort);
}

int replace_env_value(t_envp *envp, char *value)//функция поиска и изменения значения в переменных окружения
{
    char **tmp;
    int i;

    tmp = ft_split(value, '=');
    envp = search_name(envp, tmp[0]);
    if (!envp)
    {
        malloc_free(tmp);
        return (0);
    }
    // if(tmp[1] == NULL)
    //     tmp[1] = NULL;
    change_envp_value(envp, tmp[0], tmp[1]);
    data.exit_status = 0;
    // free(tmp[0]); //возможно abort
    free(tmp);
    return (1);
} 

void ft_export_next_step(t_envp **envp, char **name)
{
    t_envp *sort;
    int i;

    i = 1;
    while (name[i])
    {
        if (replace_env_value(*envp, name[i]))
            i++;
        else
        {
            if (name[i] != NULL)
            {
                *envp = export_new_name(*envp, name[i]);
                return;
            }
            sort = copy_envp(*envp, sort);
            swap_list(sort);
            sort = struct_head(sort);
            ft_lstclear(&sort);
            data.exit_status = 0;
            i++;
        }
    }
}

void ft_export(t_envp **envp, char **argv)
{
    int i;
    int j;

    i = 0;
    j = array_len(argv);
    if (!argv[1])
    {
        ft_export_next_step(envp, NULL);
        return;
    }
    while (argv[i])
    {
        if (ft_isdigit_char(argv[i][0]))
        {
            printf("minishell: export: `%s': not a valid identifier\n", argv[i]);
            data.exit_status = 1;
            return;
        }
        i++;
    }
    ft_export_next_step(envp, argv);
    return;
}

// dleaves@dleaves42:~/projects/git-mimi-01-03$ export abc 111
// bash: export: `111': not a valid identifier