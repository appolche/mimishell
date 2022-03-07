#include "../minishell.h"

void ft_pwd_print(void)
{
    char *tmp;
    tmp = getcwd(NULL, 0);
    printf("%s\n", tmp);
    free(tmp);
    data->exit_status = 0;
}

void ft_pwd(char **argv)
{
    int i;
    
    if(!argv[1])
    {
        ft_pwd_print();
        return ;
    }
    if(argv[1][0] == '-' && (argv[1][1] != 'L' && argv[1][1] != 'P'))
    {
        printf("minishell: pwd: -%c: invalid option\npwd: usage: pwd [-LP]\n", argv[1][1]);
        data->exit_status = 2;
        return ;
    }
    ft_pwd_print();
    return ;
}