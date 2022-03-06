#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

# include "./readline/readline.h"
# include "./readline/history.h"

# include "libft/libft.h"

# include <sys/uio.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_data
{
    char *str;
    char **env;
    // struct sigaction	sigac;
    int exit_status;
    // t_envp;
}   t_data;

typedef struct s_envp
{
    char *name;
    char *value;
    int key;
    int check_bit;
    struct s_envp *next;
    struct s_envp *prev;
}   t_envp;

typedef struct s_list
{
    struct s_list	*next;
    struct s_list	*prev;
    char *str;
    char *str_cmd;
    char *str_redir;
    char **cmd;
    int file_fd[2];
}   t_list;

t_data data;

//my_part
int shell_loop(t_data *data, t_envp *envp);

int syntax_errors(char *str);
int redir_syntax_errors(char *str);

void     split_for_list(char *rl_str, t_list **list);
void    parse_list(t_envp *envp, t_list *list);

//string_cutters
char *split_cmd_redir(t_list *list, char *str, int i);
char *cut_cmd_piece(char *str, int start, int i, int size);
char    *cut_quotes(char *str, int start, int end);
char    *cut_and_change_piece(char *str, int start, char *name, char *value);

char    *ft_single_quotes(char *str, int *i);
char    *ft_double_quotes(char *str, int *i, t_envp *envp);
char    *ft_dollar(char *str, int *i, t_envp *envp);

int     check_unclosed_quotes(char *str, int *i, int c);

t_list  *create_list(t_list *list, char *str, int i, int j);
t_list  *create_head(char *content);
void    ft_push_back(t_list *list, char *content);
void    make_null_init(t_list *list);
int     trim_list_strs(t_list *list);

void    list_parse(t_list *list, t_data *data);
int     check_redirs(t_list *list);
void    cut_str_cmd(t_list *list, int start);
char    *ft_substr_cpy(char *src, int *start, char c);
void parse_each_node(t_list *list);

void pipe_cmd_proc(t_list *list, char **envp);
void pipe_proc(t_list *list, char **cmd, char **envp);
void pipe_child_proc(t_list *list, char **cmd, char **envp, int pipe_fd[2]);
void pipe_parent_proc(int pipe_fd[2], pid_t pid);
void ft_exec(char **cmd, char **envp);
void path_search(char **path, char **cmd, char **envp);
void absolute_path_exec(char **cmd, char **envp);
void show_error(char *message);

void	here_doc_mode(char *limiter);
void	here_doc_child(int pipe_fd[2], char *limiter);


char	**malloc_free(char **tab);
void free_list(t_list **list);


void parse_redirect(t_list *list, char *str_redir);
char *get_file_name(char *str, int i, int *ret);


//sanya_part
int env_copy(t_data *data, char **env);
void init_t_envp(t_data *data, t_envp **envp);

t_envp *ft_lstnew(char *name, char *value);
void push_back(char *name, char *value, t_envp *check);
t_envp *search_name(t_envp *envp, char *name);
t_envp *struct_head (t_envp *envp);
void    swap_list(t_envp *list);


void ft_cd(t_envp *envp, char *command);
void ft_echo(char *av, int flag);
void ft_env(t_envp *envp);
void ft_exit(char **av);

void ft_export(t_envp *envp, char *name);
t_envp *copy_envp(t_envp *envp, t_envp *sort);
t_envp	*export_new_name(t_envp *envp, char *name);
void print_export(t_envp *list);

void ft_pwd(void);

void ft_unset(t_envp **envp, char *name);
void delete_list(t_envp **list);
void del_last_list(t_envp **envp);
void del_list(t_envp **envp);
void del_head(t_envp **envp);

void	ft_lstclear(t_envp **lst);
void free_env(t_data *data);


int ft_array_envp(t_envp *envp, t_data **data);
char    *ft_strjoin2(char *s1, char *s2);
int size_list(t_envp *envp);

#endif