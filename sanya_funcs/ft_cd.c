#include "../minishell.h"

// если пришло cd без аргументов, переходит в HOME (если его нет, "bash: cd: Не задана переменная HOME")
//"minishell: cd: HOME not set" exit.status = 1; // обработать command на NULL

//если путь не корректный или не доступен по правам выводить errno
/*
если pwd или oldpwd нет в env то они не создаються, при выходе из bash восстанавливаются старые значения
при в ходе в новый при отсутствие PWD и(или) OLDPWD  восстонавливается только PWD текущей деректории
 */
char *cd_home(t_envp *envp)
{
    t_envp *home;
    char *tmp;

    home = search_name(envp, "HOME");
    if (!home)
    {
        printf("minishell: cd: HOME not set");
        data->exit_status = 1;
        return (NULL);
    }
    tmp = home->value;
    return (tmp);
}

void ft_cd_next_step(t_envp *envp, char *command) // добавить пременую команды, можно добавить сюда переменную о сообщении, или сделать их макросоми
{
    t_envp *pwd;
    t_envp *oldpwd;

    pwd = envp;
    pwd = search_name(envp, "PWD"); // push_back
    if (!command)
        command = cd_home(envp);
    if (!command)
        return;
    if (chdir(command) == 0)
    {
        oldpwd = search_name(envp, "OLDPWD");
        oldpwd->value = pwd->value;
        pwd->value = getcwd(NULL, 0);
        data->exit_status = 0;
    }
    else
    {
        printf("bash: cd: %s: %s\n", command, strerror(errno)); //возможно стоит заменить на strerror(errno), STDERR_FILENO подробнее смотреть у вани static void	change_dir(char *new_path)
        data->exit_status = 1;
        return;
    }
}

void ft_cd(t_envp *envp, char **command)
{
    int i;

    i = array_len(command);
    if (i > 1)
    {
        printf("bash: cd: too many arguments");
        data->exit_status = 1;
        return ;
    }
    ft_cd_next_step(envp, command[1]);
}
// dleaves@dleaves42:~/projects/git-mimi-01-03$ cd ./ ../
// bash: cd: too many arguments