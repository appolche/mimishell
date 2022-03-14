#include "../minishell.h"

//в пайпах не работает

// если пришло cd без аргументов, переходит в HOME (если его нет, "bash: cd: Не задана переменная HOME")
//"minishell: cd: HOME not set" exit.status = 1; // обработать command на NULL

//если путь не корректный или не доступен по правам выводить errno
/*
если pwd или oldpwd нет в env то они не создаються, при выходе из bash восстанавливаются старые значения
при в ходе в новый при отсутствие PWD и(или) OLDPWD  восстонавливается только PWD текущей деректории
 */

// void test_prinrt(t_envp *test)
// {
//     while (test)
//     {
//         printf("test - %s = %s", test->name, test->value);
//         test = test->next;
//     }
// }
int check_pwd(t_envp *envp)
{
    int i;

    i = 0;
    if (!search_name(envp, "PWD"))
    {
        push_back(ft_strdup("PWD"), NULL, envp);
        i++;
    }
    if (!search_name(envp, "OLDPWD"))
    {
        push_back(ft_strdup("OLDPWD"), NULL, envp);
        i++;
    }
    return (i);
}

char *cd_home(t_envp *envp)
{
    t_envp *home;
    char *tmp;

    home = search_name(envp, "HOME");
    if (!home)
    {
        printf("minishell: cd: HOME not set");
        data.exit_status = 1;
        return (NULL);
    }
    tmp = home->value;
    return (tmp);
}

void change_envp_value(t_envp *envp, char *name, char *value)
{
    envp = search_name(envp, name);
    if (envp)
    {
        free (envp->value);
        envp->value = value;
    }
}

void ft_cd_next_step(t_envp *envp, char *command) // добавить пременую команды, можно добавить сюда переменную о сообщении, или сделать их макросоми
{
    t_envp *old_pwd;
    char *new_pwd;
    int check;

    check = check_pwd(envp);
    old_pwd = search_name(envp, "PWD");
    old_pwd->value = getcwd(NULL, 0);
    if (chdir(command) == 0)
    {
        change_envp_value(envp, "OLDPWD", old_pwd->value);
        new_pwd = getcwd(NULL, 0);
        change_envp_value(envp, "PWD", new_pwd);
        data.exit_status = 0;
    }
    else
    {
        printf("minishell: cd: %s: No such file or directory\n", command); //возможно стоит заменить на strerror(errno), STDERR_FILENO подробнее смотреть у вани static void	change_dir(char *new_path)
        data.exit_status = 1;
        return ;
    }
}

void ft_cd(t_envp *envp, char **command)
{
    int i;
    char *home;

    i = array_len(command);
    if (i > 1)
    {
        printf("minishell: cd: too many arguments\n");
        data.exit_status = 1;
        return;
    }
    if (command[1] == NULL)
    {
        home = cd_home(envp);
        if (!home)
            return ;
        check_pwd(envp);
        ft_cd_next_step(envp, home);
    }
    else
        ft_cd_next_step(envp, command[1]);
}
