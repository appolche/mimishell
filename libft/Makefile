NAME = libft.a

INCLUDES = ./

HEADER = libft.h

SRCS = ft_isalnum.c ft_split.c ft_strchr.c ft_strcmp.c ft_strdup.c ft_strjoin.c\
	   ft_strlcpy.c ft_strlen.c ft_strnstr.c ft_strtrim.c ft_substr.c ft_isdigit.c\
	   ft_atoi.c

OBJ = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c
	gcc -c -Wall -Wextra -Werror -g -I $(INCLUDES) -o $@ $<

clean: 
	rm -f $(OBJ)
	:
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean flean re