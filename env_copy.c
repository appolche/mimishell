#include "minishell.h"

t_envp *init_t_envp(t_data *data, t_envp *envp) // инцилизация t_envp
{
    int i = 0;
    char **tmp;
   
    while (data->env[i])
    {
        tmp = ft_split(data->env[i], '=');
        if (envp == NULL)
            envp = ft_lstnew(tmp[0], tmp[1]);
        else
            push_back(tmp[0], tmp[1], envp);
           free(tmp);
        i++;
    }
    return (envp);
}

int env_copy(t_data *data, char **env)
{
    int i;
    int j;

    i = 0;
    j = -1;
    while (env[i] != NULL)
        i++;
    data->env = (char **)malloc(sizeof(char *) * (i + 1));
    if (!data->env)
        return (1);
    while (env[++j] != NULL)
    {
        data->env[j] = ft_strdup(env[j]);
        if (!data->env[j])
            return (1);
    }
    data->env[j] = NULL;
    return (0);
}