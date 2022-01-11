#ifndef MINISHELL_H

# define MINISHELL_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <termios.h>//добавить в мейк -ltermcap
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

typedef struct s_data
{
    char *str;
    char **env;
}   t_data;

typedef struct s_cmd
{
    char **cmd;
}   t_cmd;

int env_copy(t_data *data, char **env);
void free_env(t_data *data);
char *lexer(char *str, char **env);
char *ft_quotes(char *str, int *i);
char *ft_double_quotes(char *str, int *i, char **env);
char *ft_backslash(char *str, int *i);
char *ft_dollar(char *str, int *i, char **env);
int ifkey(char c);


#endif