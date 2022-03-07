#include "../minishell.h"

int check_flag(char *str)
{
    int i;

    i = 1;
    while(str[i])
    {
        if(str[0] != '-' || str[i] != 'n')
            return (0);
        i++; 
    }
    return (1);
}

void ft_echo_next_step(char *av, int flag)
{
    if (flag == 1)
        printf("%s", av);
    else
        printf("%s\n", av);
    data->exit_status = 0;
    return ;
}

void ft_echo(char **av)
{
    int flag;
    int i;

    i = array_len(av);
    if (i > 1)
    {
        printf("\n");
        data->exit_status = 0;
        return ;
    }
    flag = check_flag(av[1]);
    if(flag == 1 && i == 2)
    {
        printf("\r");
        data->exit_status = 0;
        return ;
    }
    if(flag == 1)
        i = 2;
    else
        i = 1;
    while(av[i])
        ft_echo_next_step(av[i++], flag);
    data->exit_status = 0;
    return ; 
}
//echo
//-n-n-n-n
//argument