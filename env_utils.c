#include "minishell.h"

void free_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
		free(data->env[i++]);
	free(data->env);
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

