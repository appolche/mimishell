#include "../minishell.h"

void print_export(t_envp *list)
{
    printf("\n\n");
    while(list)
   {
        if(list->value == NULL)
            printf("declare -x %s=\"\"\n", list->name);
        else
            printf("declare -x %s=\"%s\" \n", list->name, list->value);
        list = list->next;
   }
}

t_envp	*export_new_name(t_envp *envp, char *name)
{
	char **tmp;
	int check;
	int i;

	i = 0;
	tmp = (char **)malloc(sizeof(char *) * 2);
	check = ft_strchr(name, '=');
	if(check == 0)
	{
		tmp[0] = ft_strdup(name);
		tmp[1] = NULL;
	}
	else
	{
		free(tmp);
		tmp = ft_split(name, '=');
	}
	if(!tmp)
		exit(2);
    push_back(tmp[0], tmp[1], envp);
	envp = struct_head(envp);
	free(tmp);
	return (envp);
}

t_envp *copy_envp(t_envp *envp, t_envp *sort)
{
    t_envp *tmp;
    char *name;
    char *value;
    char *as;
    char *as2;

    as = ft_strdup("enddd");
    as2 = ft_strdup("enddd");
    tmp = envp;
    sort = NULL;
    while (tmp)
    {
        name = ft_strdup (tmp->name);
        if (tmp->value == NULL)
            value = NULL;
        else
            value =ft_strdup(tmp->value);
        if(!sort)
            sort = ft_lstnew(name, value);            
        else
            push_back(name, value, sort);
        tmp = tmp->next;
    }
    push_back(as, as2, sort);
    sort = struct_head(sort);
    return (sort);
}

void ft_export(t_envp *envp, char *name)
{
    t_envp *sort;

    if(name != NULL)
        envp = export_new_name(envp, name);
    sort = copy_envp(envp, sort);
    swap_list(sort);
    sort = struct_head(sort);
    ft_lstclear(&sort);
}