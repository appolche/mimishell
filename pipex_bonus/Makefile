NAME = pipex
BONUS_NAME = pipex_bonus

SRC = pipex.c execution.c
SRC_B = bonus/pipex_bonus.c bonus/utils_bonus.c bonus/execution_bonus.c bonus/heredoc_bonus.c

OBJS = $(SRC:.c=.o)
OBJS_B = $(SRC_B:.c=.o)

FLAGS = -Wall -Werror -Wextra -g
LFLAGS = -L $(LDIR) -lft
LDIR = ../libft/

HEADER	= pipex.h libft/libft.h
HEADER_B	= bonus/pipex_bonus.h libft/libft.h

all: $(NAME)
			make -C ${LDIR}

$(NAME): $(OBJS) $(HEADER)
	make -C $(LDIR)
	clang -o $(NAME) $(FLAGS) $(OBJS) $(LFLAGS)

bonus: $(BONUS_NAME)
			make -C ${LDIR}
		mv pipex_bonus pipex

$(BONUS_NAME): $(OBJS_B) $(HEADER_B)
	make -C $(LDIR)
	clang -o $(BONUS_NAME) $(FLAGS) $(OBJS_B) $(LFLAGS)

clean:
	make clean -C $(LDIR)
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	make fclean -C $(LDIR)
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all, clean, fclean, re, bonus
