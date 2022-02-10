NAME = mimishell

SRC = main.c lexer.c env_utils.c execute.c fd_proc.c list_tools.c pipex.c

OBJS = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra -lreadline
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