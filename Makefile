NAME = minishell

REBUILT_FUNCS = ./sanya_funcs/ft_cd.c \
					./sanya_funcs/ft_echo.c \
					./sanya_funcs/ft_env.c \
					./sanya_funcs/ft_exit.c \
					./sanya_funcs/ft_export.c \
					./sanya_funcs/ft_pwd.c \
					./sanya_funcs/ft_unset.c \
					./sanya_funcs/shlvl.c \

SRC = main.c signal.c path_and_exec.c fd_parse.c my_cmd_proc.c heredoc.c env_copy.c env_list_tools.c swap_val_list.c parser.c errors.c string_cutters.c quotes.c dollar.c list_tools.c pipe_executor.c $(REBUILT_FUNCS)

OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra -g -lreadline -L ~/.brew/opt/readline/lib -I~/.brew/opt/readline/include
LFLAGS = -L $(LDIR) -lft
LDIR = ./libft/

HEADER	= minishell.h libft/libft.h

all: $(NAME)
			make -C ${LDIR}

$(NAME): $(OBJS) $(HEADER)
	make -C $(LDIR)
	clang -o $(NAME) $(FLAGS) $(OBJS) $(LFLAGS)

clean:
	make clean -C $(LDIR)
	rm -f $(OBJS) 

fclean: clean
	make fclean -C $(LDIR)
	rm -f $(NAME) 

re: fclean all

.PHONY: all, clean, fclean, re