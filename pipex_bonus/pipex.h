#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define BUFFER_SIZE 10000

void	choose_mode(char **argv, int *file_fd, int *i);
void	here_doc_mode(char *limiter, int file_fd[2]);
void	here_doc_child(int pipe_fd[2], char *limiter);
void	cmd_proc(char *argv, char **envp, int file_fd[2]);
void	child_proc(char *argv, char **envp, int pipe_fd[2], int file_fd[2]);
void	parent_proc(int pipe_fd[2], int file_fd[2], pid_t pid);
void	ft_exec(char **cmd, char **envp);
void	path_search(char **path, char **cmd, char **envp);
void	absolute_path_exec(char **cmd, char **envp);
char	*gnl_stdin(int fd);
void	show_error(char *message);

#endif
