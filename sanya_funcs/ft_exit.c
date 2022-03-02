#include "../minishell.h"

int        ft_strcheck(const char *s1, const char s2)
{
    const unsigned char *p1;
    p1 = (const unsigned char *)s1;

    while (*p1)
    {
        if(*p1 == s2)
            return(1);
        ++p1;
    }
    return (0);
}
char *ft_word(char *str)
{
    int i;
    int j;
    char *word;
    word = malloc(ft_strlen(str) + 1);
    i = 0;
    j = 0;
    while (str[i])
    {
        if(str[i] == '(' || str[i] == ')')
            i++;
        word[j++] = str[i++];
    }
    word[j] = '\0';
    return (word);
}

char *check_bracket(char **av)
{
    int i;
    char *tmp1;
    char *tmp2;
    
    tmp1 = ft_strdup("(");
    tmp2 = ft_strdup(")");
    i = 0;
    if(av[1][0] == '(')
        return (ft_word(av[1]));
    while (av[i])
    {
        if(ft_strcheck(av[i], '('))
            return(tmp1);
        if(ft_strcheck(av[i], ')'))
            return(tmp2);
        i++;
    }
    return (NULL);
}

int    ft_isalldigit(char *str)
{
    int    i;

    i = 0;
    if (str[0] == '-')
        i++;
    while (str[i])
    {
        if (!ft_isdigit((unsigned char)str[i]) || ft_strlen(str) >= 19)
            return (1);
        i++;
    }
    return (0);
}

int array_len(char **av)
{
    int i;

    i = 0;
    while (av[i])
        i++;
    return (i);
}

void ft_out(int value, int flag, char *av)
{
    // rl_clear_history();
    data.exit_status = (unsigned char)value;
    printf("exit\n");
    if(flag == 1)
        printf("bash: exit: %s: numeric argument required\n", av);
    if(flag == 2)
    {
        printf("bash: exit: too many arguments\n");
        return ;
    }
    exit(value);
}

void ft_exit(char **av)
{
    int i;
    char *str;

    if(!av)
        return ;
    i = array_len(av);
    if(i == 1)
        ft_out(0, 0, NULL);
    str = check_bracket(av);
    if(str)
    {
        printf("bash: syntax error near unexpected token `%s'\n", str);
        free(str);
        data.exit_status = 258;
        return ;
    }
    if(i > 1)
    {
        if(ft_isalldigit(av[1]))
            ft_out(255, 1, av[1]);
        else if(i > 2)
            ft_out(1, 2, NULL);
        else
            ft_out((unsigned char)ft_atoi(av[1]), 0, NULL);
    }
    return ;
}
