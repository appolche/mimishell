#include "minishell.h"

int size_list(t_envp *envp)
{
    int size;

    size = 0;
    while (envp)
    {
        size++;
        envp = envp->next;
    }
    return (size);
}

char    *ft_strjoin2(char *s1, char *s2)
{
    char    *s3;
    int     i;
    int     j;
    if (!s1 || !s2)
        return (NULL);
    s3 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
    if (!s3)
        return (NULL);
    i = 0;
    j = 0;
    while (s1[i])
    {
        s3[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        s3[j + i] = s2[j];
        j++;
    }
    s3[j + i] = '\0';
    return (s3);
}

int ft_array_envp(t_envp *envp, t_data **data) //
{
    char *tmp;
    char *string;
    int i;

    tmp = ft_strdup("=");
    if ((*data)->env)
        (*data)->env = malloc_free((*data)->env);
    (*data)->env = (char **)malloc((size_list(envp) + 1) * sizeof(char *));
    if (!(*data)->env)
        return (0);
    i = 0;
    while (envp)
    {
        string = ft_strjoin2(envp->name, tmp);
        (*data)->env[i] = ft_strjoin2(string, envp->value);
        free(string);
        i++;
        envp = envp->next;
    }
    (*data)->env[i] = NULL;
    free(tmp);
    return (1);
}

void init_t_envp(t_data *data, t_envp **envp) // инцилизация t_envp
{
    char **tmp;
    char *name;
    char *value;
    int i;
    
    i = 0;
    tmp = NULL;
    while (data->env[i])
    {
        tmp = ft_split(data->env[i], '=');
        name = ft_strdup(tmp[0]);
        value = ft_strdup(tmp[1]);
        malloc_free(tmp);
        if (*envp == NULL)
            *envp = ft_lstnew(name, value);
        else
            push_back(name, value, *envp);
        i++;
    }
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