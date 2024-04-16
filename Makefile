NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -lreadline
CLIBFT = src/libft/ft_strjoin.c src/libft/ft_split.c src/libft/ft_strlen.c src/libft/ft_calloc.c src/libft/ft_strlcpy.c \
         src/libft/ft_bzero.c src/libft/ft_strncmp.c src/libft/ft_substr.c 
OLIBFT = $(CLIBFT:.c=.o)
SRCS = src/main.c src/get_path.c
OBJS = $(SRCS:.c=.o)
RM = rm -f
AR = ar
ARFLAGS = -rcs

all: $(NAME)

$(NAME): $(OBJS) $(OLIBFT)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OLIBFT)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re