/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:29:35 by dleaves           #+#    #+#             */
/*   Updated: 2022/03/19 18:29:37 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_envp
{
	struct s_envp	*next;
	struct s_envp	*prev;
	char			*name;
	char			*value;
	int				key;
	int				check_bit;
}	t_envp;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*str;
	char			*str_cmd;
	char			*str_redir;
	char			**cmd;
	int				file_fd[2];
}	t_list;

typedef struct s_data
{
	char	*str;
	char	**env;
	int		exit_status;
	sig_t	sig_int;
	sig_t	sig_quit;
	t_envp	*envp;
}	t_data;

t_data	g_data;

/*my_part*/
int		shell_loop(t_data *data, t_envp *envp);
int		prepars_syntax_errors(char *str);
int		syntax_errors(char *str, int i);
int		redir_syntax_errors(char *str, int i);
int		split_for_list(char *rl_str, t_list **list);
int		parse_list(t_envp *envp, t_list *list);
/*string_cutters*/
char	*split_cmd_redir(t_list *list, char *str, int i);
char	*cut_cmd_piece(char *str, int start, int i, int size);
char	*cut_quotes(char *str, int start, int end);
char	*cut_and_change_piece(char *str, int start, char *name, char *value);
char	*ft_single_quotes(char *str, int *i);
char	*ft_double_quotes(char *str, int *i, t_envp *envp);
char	*ft_dollar(char *str, int *i, t_envp *envp);
int		skip_some_chars(char *str, int i);
int		check_unclosed_quotes(char *str, int *i, int c);
/*lists*/
t_list	*create_list(t_list *list, char *str, int i, int j);
t_list	*create_head(char *content);
char	*ft_substr_cpy(char *src, int *start, char c);
void	ft_push_back(t_list *list, char *content);
void	make_null_init(t_list *list);
void	list_parse(t_list *list, t_data *data);
void	cut_str_cmd(t_list *list, int start);
void	parse_each_node(t_list *list);
int		trim_list_strs(t_list *list);
int		check_redirs(t_list *list);
/*pipes*/
void	pipe_cmd_proc(t_list *list, t_envp *envp);
void	pipe_proc(t_list *list, char **cmd, t_envp *envp);
void	pipe_child_proc(t_list *list, char **cmd, int pipe_fd[2], t_envp *envp);
void	pipe_parent_proc(int pipe_fd[2], pid_t pid);
void	ft_exec(char **cmd, t_envp *env_list);
void	path_search(char **path, char **cmd, char **envp);
void	absolute_path_exec(char **cmd, char **envp);
void	show_error(char *message);
char	**make_env_array(t_envp *envp);
int		check_first_cmd(t_list *list, t_envp *envp);
/*cmds*/
int		is_my_command(t_list *list);
int		check_my_cmd(char **cmd);
void	exec_my_cmd(t_list *list, t_envp *envp);
void	exec_my_single_cmd(t_list *list, t_envp *envp);
/*heredoc*/
int		here_doc_mode(char *limiter);
void	here_doc_child(int pipe_fd[2], char *limiter);
/*free*/
char	**malloc_free(char **tab);
void	free_list(t_list **list);
/*redirect*/
void	parse_redirect(t_list *list, char *str_redir);
char	*get_file_name(char *str, int i, int *ret);
char	*filename_in_quotes(char *str, int *i, int c);
void	open_file(t_list *list, char *redir_type, char *file_name);
void	open_output_fd(t_list *list, char *redir_type, char *file_name);
void	open_input_fd(t_list *list, char *redir_type, char *file_name);
void	redirect_fd(t_list *list);
void	redirect_rebuilts_fd(t_list *list);
/*sanya_part*/
int		env_copy(t_data *data, char **env);
t_envp	*ft_lstnew(char *name, char *value);
void	init_t_envp(t_data *data, t_envp **envp);
void	push_back(char *name, char *value, t_envp *check);
void	swap_list(t_envp *list);
t_envp	*search_name(t_envp *envp, char *name);
t_envp	*struct_head(t_envp *envp);
/*cd*/
void	ft_cd(t_envp *envp, char **command);
void	ft_cd_next_step(t_envp *envp, char *command);
char	*cd_home(t_envp *envp);
void	change_envp_value(t_envp *envp, char *name, char *value);
/*echo*/
void	ft_echo(char **av);
void	ft_echo_next_step(char *av, int flag);
int		check_flag(char *str);
/*env*/
void	ft_env(t_envp *envp, char **argv);
void	ft_env_next_step(t_envp *envp);
/*exit*/
void	ft_exit(char **av);
int		array_len(char **av);
/*export*/
int		ft_isdigit_char(char c);
void	ft_export(t_envp **envp, char **argv);
void	ft_export_next_step(t_envp **envp, char *name);
void	print_export(t_envp *list);
t_envp	*copy_envp(t_envp *envp, t_envp *sort);
t_envp	*export_new_name(t_envp *envp, char *name);
/*pwd*/
void	ft_pwd(char **argv);
void	ft_pwd_print(void);
/*unset*/
void	ft_unset(t_envp **envp, char **name);
void	ft_unset_next_step(t_envp **envp, char *name);
void	delete_list(t_envp **list);
void	del_last_list(t_envp **envp);
void	del_list(t_envp **envp);
void	del_head(t_envp **envp);
/*free*/
void	ft_lstclear(t_envp **lst);
void	free_env(t_data *data);
char	*ft_strjoin2(char *s1, char *s2);
int		ft_array_envp(t_envp *envp, t_data **data);
int		size_list(t_envp *envp);
/*SHLVL*/
void	ft_shlvl(t_envp *envp);
int		lookup_name_replace_value(t_envp *envp, char **value);
/* norm */
void	delete_list(t_envp **list);
void	print_export(t_envp *list);
char	*ft_word(char *str);
char	*check_bracket(char **av);
char	*check_bracket_v2(char *av);
int		ft_isdigit_char(char c);
int		array_len(char **av);
int		ft_strcheck(const char *s1, const char s2);
int		change_envp(t_envp *envp, char *str);
int		error_valid(char **argv, int i);
/* signal */
void	signal_handler(int sig);
void	set_default_sig(void);
void	set_custom_sig(void);
void	disable_sig(void);
void	sig_init(void);

#endif
