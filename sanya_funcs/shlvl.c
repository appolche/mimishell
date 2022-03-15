#include "../minishell.h"
// принимаем строку
// проверить =, если его нет это не команда ft_strchr(name, '=');
// команда не найдена exit_status = 127
//проверить есть ли value, shlvl=0 (export_new_name переписать)
// проверить на буквы или спецсимвол, если они есть shlvl=0 (ft_isalldigit(char *str))
//если пришло число значение value-1, число записать строкой
//если пришло число < 0, shlvl =0
//если число привышает 998, shlvl = 1

// на макек 
// пишет все 
// при переходе на новый уровень проверяет, что записано если это не число SHLVL=1


//bash-3.2$ SHLVL=$SHLVL+100
// bash-3.2$ env | grep SHLVL
// SHLVL=2+100

// SHLVL=1000
// bash-3.2$ bash
// bash: warning: shell level (1001) too high, resetting to 1
// bash-3.2$ echo $?
// 0

//если SHLVL больше 999
// SHLVL=999
// bash-3.2$ bash
// bash-3.2$ env | grep SHLVL
// SHLVL=

void free_mass(char **str)
{
    int i;

    i = 0;
    while(str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

int lookup_name_replace_value(t_envp *envp, char **value)//функция поиска и изменения значения в переменных окружения
{
    char **tmp;
    int i;

    tmp = (char **)malloc(sizeof(char *) * 2);
    if (value[1])
    {
        printf("minishell: %s: command not found\n", value[1]);
        data.exit_status = 127;
        return (0);
    }
    i = ft_strchr(value[0], '=');
    if (i == 0)
        return (0);
    tmp = ft_split(value[0], '=');
    envp = search_name(envp, tmp[0]);
    if (!envp)
    {
        free_mass(tmp);
        return (0);
    }
    change_envp_value(envp, tmp[0], tmp[1]);
    data.exit_status = 0;
    free(tmp[0]); //возможно abort
    free(tmp);
    return (1);
} 

int check_value(char *str)
{
    int i;

    i = 0;
    
    while (str[i])
    {
        if (ft_isdigit_char(str[i]))
            return (1);
        i++;
    }
    return (0);
}


void ft_shlvl(t_envp *envp)
{
    int i;
    char *tmp;

    data.exit_status = 0;
    envp = search_name(envp, "SHLVL");
    if (!envp)
    {
        push_back(ft_strdup("SHLVL"), NULL, envp);
        return ;
    }
    if (!envp->value)
    {
        envp->value = ft_itoa(0);
        return ;
    }
    if (check_value(envp->value) == 0)
    {
        free(envp->value);
        envp->value = ft_itoa(1);
        return ;
    }
    else
    {
        i = ft_atoi(envp->value) + 1;
        if (i == 1000)
        {
            free(envp->value);
            envp->value = NULL;
            return ;
        }
        else if (i >= 1001)
        {
            printf("minishell: warning: shell level (1001) too high, resetting to 1\n");
            free(envp->value);
            envp->value = ft_itoa(1);
            return ;
        }
        else
        {
            free(envp->value);
            envp->value = ft_itoa(i);
            data.exit_status = 0;
            return ;
        }
    }  
}