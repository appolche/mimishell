#include "../minishell.h"

int check_flag(char *str)
{
    int i;

    i = 1;
    while (str[i])
    {
        if (str[0] != '-' || str[i] != 'n')
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
    return;
}

void printf_char(char **test)
{
    int i = 0;

    while (test[i])
    {
        printf("%s\n", test[i]);
        i++;
    }
}

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void ft_echo(char **av)
{
    int flag;
    int i;

    // printf_char(av);
    i = array_len(av);
    if (i == 0)
    {
        printf("\n");
        data->exit_status = 0;
        return;
    }
    flag = check_flag(av[1]);
    // printf("flag = %d\n", flag);
    if (flag == 1 && i == 1)
    {
        printf("\r");
        data->exit_status = 0;
        return;
    }
    if (flag == 1)
        i = 2;
    else
        i = 1;
    while (av[i])
    {
        if (flag == 1)
        {
            ft_putstr_fd(av[i], 1);
            if (av[i + 1])
                write(1, " ", 1);
        }
        else
        {
            ft_putstr_fd(av[i], 1);
            if (av[i + 1])
                write(1, " ", 1);
            else
                write(1, "\n", 1);
        }
        i++;
    }
    data->exit_status = 0;
    return;
}
// echo
//-n-n-n-n
// argument