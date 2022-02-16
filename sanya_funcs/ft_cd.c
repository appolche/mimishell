#include "../minishell.h"

void ft_cd(t_envp *envp) // добавить пременую команды, можно добавить сюда переменную о сообщении, или сделать их макросоми
{
    t_envp *pwd;
    t_envp *oldpwd;
    char *command = "../../"; //должна приходить из вне в виде строчки.
    pwd = envp;
    pwd = search_name(envp, "PWD");
    if(chdir(command) == 0)
    {
        oldpwd = search_name(envp, "OLDPWD");
        oldpwd->value = pwd->value;
        pwd->value = getcwd(NULL, 0); 
    }
     else
     {
         printf("bash: cd: %s: No such file or directory\n", command);//возможно стоит заменить на strerror(errno), STDERR_FILENO подробнее смотреть у вани static void	change_dir(char *new_path)
        // $? = 1;
        return ;
     }
}