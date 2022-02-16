#include "../minishell.h"

void ft_echo(char *av, int flag)
{
    if(flag == 1)
        printf("%s", av);
    else if(!av)
        printf("\n");
    else
        printf("%s\n", av);
    //$? = 0;
}