#include "minishell.h"

int shell_loop(t_data *data, char **argv)
{   
    char *str;
    while(1)
    {
        write(1, "minishell: ", 11);
        data->str = get_next_line(0);
	    if (data->str == NULL)
	    {
		    ft_putstr_fd("exit\n", 1);
		    return (1);
	    }
        str = lexer(data->str, data->env);
        printf("%s", str);
    }
}

int main(int argc, char **argv, char **env)
{
    t_data *data;

    data = malloc(sizeof(t_data));
    if (env_copy(data, env) == 1)
        return (1);
    shell_loop(data, argv);
    
    free_env(data);
    free(data);
    return (0);
}