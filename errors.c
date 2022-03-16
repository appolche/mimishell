#include "minishell.h"

int syntax_errors(char *str)
{
    int i;
    int c;

    i = -1;
    c = 0;
    while (str[++i])
    {
        if (str[0] == '|')
        {
            printf("minishell: syntax error near unexpected token `|'\n");
            return (1);
        }
        else if (str[i] == '|' && str[i + 1] == '\0')
        {
            printf("minishell: error: no command after pipe\n");
            return (1);
        }
        else if ((str[i] == '>' || str[i] == '<') && str[i + 1] == '|')
        {
            printf("minishell: syntax error near unexpected token `|'\n");
            return (1);
        }
        else if (str[i] == '|')
        {
            c = 0;
            while (str[i] == '|')
            {
                c++;
                i++;
            }
            if (c > 1)
            {
                printf("minishell: syntax error near unexpected token `|'\n");
                return (1);
            }
        }
    }
    return (0);
}

int redir_syntax_errors(char *str)
{
    int c;
    int i;

    i = -1;
    c = 0;
    while (str[++i])
    {
        if ((str[i] == '>' || str[i] == '<') && str[i + 1] == '\0')
        {
                printf("minishell: syntax error near unexpected token `newline'\n");
                return (1);
        }
        if (str[i] == '>')
        {
            i++;
            if (str[i] == '<')
            {
                printf("minishell: syntax error near unexpected token `<'\n");
                return (1);
            }
            else if (str[i] == '>' && str[i + 1] == '>')
            {
                printf("minishell: syntax error near unexpected token `>>'\n");
                return (1);
            }
            else if (str[i] == ' ' && str[i + 1] == '>')
            {
                printf("minishell: syntax error near unexpected token `>'\n");
                return (1);
            }
        }
        else if (str[i] == '<')
        {
            if (str[i + 1] == '<' && str[i + 2] == '\0')
            {
                printf("minishell: syntax error near unexpected token `newline'\n");
                return (1);
            }
            c = 0;
            while (str[i] == '<')
            {
                c++;
                i++;
            }
            if (c > 3)
            {
                printf("minishell: syntax error near unexpected token `<<'\n");
                return (1);
            }
            else if (c >= 2 && str[i] == '>')
            {
                printf("minishell: syntax error near unexpected token `>'\n");
                return (1);
            }
            else if (str[i] == ' ' && str[i + 1] == '<')
            {
                printf("minishell: syntax error near unexpected token `<'\n");
                return (1);
            }
        }
    }
    return (0);
}