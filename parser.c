#include "minishell.h"

// "", '', \, $, ;, |, >, >>, <, ' ' (пробел. в кавычках перестает быть служебным. пробел игнорится до и после команды)
// ; - последовательное выполнение команд. распарсить все на команды по ; потом уже парсить все команды
/* редирект
 > FILENAME
    fd[1] = open("FILENAME", O_WRONLY | O_CREAT | O_TRUNC, 0644); // O_TRUNC - зачищает файл
    if(fd[1] == -1)
        printf("%s: %s\n", FILENAME, strerror(errno)); //вывод ошибок во второй канал
 >> FILENAME
    open("FILENAME", O_WRONLY | O_CREAT | O_APPEND, 0644); // O_APPEND - дописывает в файл
    printf("%s\n", strerror(errno));
 < FILENAME
    open("FILENAME", O_RDONLY, 0644);
    printf("%s\n", strerror(errno));
 */ 
int ifkey(char c)
{
    if (c == '_' || ft_isalnum(c))
        return (1);
    return(0);
}

char    *ft_dollar(char *str, int *i, char **env)
{
    //$? - обработать -  возвращает код последней отработавшей программы
    int j;
    int k;
    char *key;
    char *tmp2;
    int z;

    k = -1;
    j = *i;
    z = 0;
    while (str[++(*i)])
    {
        if (!ifkey(str[*i]))
            break;
    }
    if (*i == j + 1)
        return (str);
    key = ft_substr(str, j + 1, *i - j - 1);
    while (env[++k])
    {
        if (strstr(env[k], key)) //написать свой стрстр
		{
            z = 0;
            while (env[k][z] && env[k][z] != '=')
                z++;
            tmp2 = ft_substr(env[k], 0, z);
            if (strcmp(key, tmp2) == 0) //написать свой стркмп
                break;
		}
    }
    tmp2 = ft_substr(env[k], z + 1, strlen(env[k]) - z);
    //убрать $USER заменить на dleaves

    printf("KEY = %s\n", tmp2);
    //free(str);
    return (str);

}

char *ft_backslash(char *str, int *i)
{
    char *tmp;
    char *tmp2;

    if (str[*i + 1] == '\\')
    {
        tmp = ft_substr(str, 0, *i + 1);
        tmp2 = ft_strdup(str + *i);
        tmp = ft_strjoin(tmp, tmp2);
        free(str);
        ++(*i);
        printf("backslash_tmp = %s\n", tmp);
        return (tmp);
    }
            //ft_backslash(str, i);
    tmp = ft_substr(str, 0, *i);
    tmp2 = ft_strdup(str + *i + 1);
    tmp = ft_strjoin(tmp, tmp2);
    free(str);
    ++(*i);
    printf("backslash_tmp = %s\n", tmp);
    return (tmp);
}

char *ft_quotes(char *str, int *i)
{
    int j;
    char *tmp;
    char *tmp2;
    char *tmp3;

    j = *i;
    while (str[++(*i)])
    {
        if (str[*i] == '\'')
            break;
    }
    tmp = ft_substr(str, 0, j);
    tmp2 = ft_substr(str, j + 1, *i - j - 1);
    tmp3 = ft_strdup(str + *i + 1);
    tmp = ft_strjoin(tmp, tmp2);
    tmp = ft_strjoin(tmp, tmp3);
    printf("quote_tmp = %s\n", tmp);
    free(str);
    return (tmp);
}

char *ft_double_quotes(char *str, int *i, char **env)
{
    int j;
    char *tmp;
    char *tmp2;
    char *tmp3;

    j = *i;
    while (str[++(*i)])
    {
        if (str[*i] == '\\' && (str[*i + 1] == '\"' || str[*i + 1] == '$' || str[*i + 1] == '\\'))
            ft_backslash(str, i);
        if (str[*i] == '$')
            ft_dollar(str, i, env);
        if (str[*i] == '\"')
            break;
    }
    tmp = ft_substr(str, 0, j);
    tmp2 = ft_substr(str, j + 1, *i - j - 1);
    tmp3 = ft_strdup(str + *i + 1);
    tmp = ft_strjoin(tmp, tmp2);
    tmp = ft_strjoin(tmp, tmp3);
    printf("double_quotes_tmp = %s\n", tmp);
    free(str);
    return (tmp);
}

void parser(char *str, char **env)
{
    int i;

    i = -1;
    
    while(str[++i])
    {
        if (str[i] == '\"')
            str = ft_double_quotes(str, &i, env);
        if (str[i] == '\'')
            str = ft_quotes(str, &i);
        if (str[i] == '\\')
            str = ft_backslash(str, &i);
        if (str[i] == '$')
            str = ft_dollar(str, &i, env);
    }

}

int main(int argc, char **argv, char **env)
{
    char *str = ft_strdup(argv[1]);

    //preparser (lexer) (проверка на закрытие кавычки и другая валидность. error mngmt || ;; |; начало с ; начало с | ...)
    parser(str, env);
}