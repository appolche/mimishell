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
//# include "gnl/get_next_line.h"

typedef struct s_data
{
    char *str;
    char **env;
}   t_data;

                // if (i != 0)
                // {
                //     list->str_cmd = ft_substr(list->str, 0, i);
                //     if (!list->str_cmd)
                //         return (1);
                // }
                // else 
                //     if(list->str_cmd)
                //         free(list->str_cmd);

typedef struct s_list
{
    struct s_list	*next;
    struct s_list	*prev;
    char *str;
    char *str_cmd;
    char *str_redir;
    char **cmd;
    char **redir;
}   t_list;

int env_copy(t_data *data, char **env);
void free_env(t_data *data);
char *lexer(char *str, char **env);
char *ft_quotes(char *str, int *i);
char *ft_double_quotes(char *str, int *i, char **env);
char *ft_backslash(char *str, int *i);
char *ft_dollar(char *str, int *i, char **env);
int ifkey(char c);
t_list *create_list(char *content);
void ft_push_back(t_list *list, char *content);

void	ft_exec(char **cmd, char **envp);
void	path_search(char **path, char **cmd, char **envp);
void		absolute_path_exec(char **cmd, char **envp);
void one_cmd_proc(char **cmd, char **env);
void show_error(char *message);

void pipe_cmd_proc(t_list *list, char **envp);
void	pipe_proc(char **cmd, char **envp);
void	pipe_child_proc(char **cmd, char **envp, int pipe_fd[2]);
void	pipe_parent_proc(int pipe_fd[2], pid_t pid);

t_list *list_cmds(t_list **list, char *str);
t_list *add_list(t_list **list, char *str, int *i, int *j);

#endif
