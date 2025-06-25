NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ../libft
LIBFT_A = $(LIBFT_DIR)/libft.a

SRCS = ft_printf.c tools.c
OBJS = $(SRCS:.c=.o)

all: $(LIBFT_A) $(NAME)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

%.o: %.c ft_printf.h
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re