NAME = minishell
NAME_BONUS = minishell_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address,leak

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a

SRCS = srcs/*.c srcs/builtins/*.c srcs/exec/*.c srcs/expansion/*.c srcs/heredoc/*.c srcs/identification/*.c srcs/readline/*.c srcs/redirections/*.c srcs/s_minishell/*.c srcs/tokenization/*.c srcs/history/*.c srcs/main/*.c srcs/cleaning/*.c srcs/env/*.c srcs/utils/*.c
SRCS_BONUS = srcs_bonus/*.c srcs_bonus/builtins/*.c srcs_bonus/exec/*.c srcs_bonus/expansion/*.c srcs_bonus/heredoc/*.c srcs_bonus/identification/*.c srcs_bonus/readline/*.c srcs_bonus/redirections/*.c srcs_bonus/s_minishell/*.c srcs_bonus/tokenization/*.c srcs_bonus/history/*.c srcs_bonus/cleaning/*.c srcs_bonus/env/*.c srcs_bonus/utils/*.c

INCLUDES = -Itokenization -I. -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR)
LIBS = -lreadline -L$(LIBFT_DIR) -lft
#-Lpath look for .a or .so in path, -lft tell to use .a
#		-lft: search for libDIR_NAME.a in /DIR_NAME

draw:
	@echo "\033[0;35m"
	@echo "        _       _   __ _          _ _ "
	@echo "  /\\/\\ (_)_ __ (_) / _\\ |__   ___| | |"
	@echo " /    \\| | '_ \\| | \\ \\| '_ \\ / _ \\ | |"
	@echo "/ /\\/\\ \\ | | | | | _\\ \\ | | |  __/ | |"
	@echo "\\/    \\/_|_| |_|_| \\__/_| |_|\\___|_|_|"
	@echo "                                                         by @sbehar and @van-nguy"
	@echo "\033[0m"

all: $(LIBFT_A) $(FT_PRINTF) $(NAME)

$(LIBFT_A):
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

$(FT_PRINTF):
	@$(MAKE) --no-print-directory -C $(FT_PRINTF_DIR)

$(NAME):
	@$(CC) $(INCLUDES) $(CFLAGS) $(SRCS) $(FT_PRINTF) $(LIBFT_A) $(LIBS) -o $(NAME)
	@echo "Minishell compiled successfully!"
	@make --silent clean

bonus: $(LIBFT_A) $(FT_PRINTF)
	@$(CC) $(INCLUDES) $(CFLAGS) $(SRCS_BONUS) $(FT_PRINTF) $(LIBFT_A) $(LIBS) -o $(NAME_BONUS)
	@echo "Minishell compiled successfully!"
	@make --silent clean

clean:
	@rm -rf *.o
	@echo "Cleaned up object!"

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
	@$(MAKE) --no-print-directory -C $(FT_PRINTF_DIR) fclean
	@echo "Fully cleaned up the project!"

re: fclean all

re_bonus: fclean bonus

tester:
	git clone https://github.com/LucasKuhn/minishell_tester.git

norminette:
	norminette $(SRCS)

.PHONY: all clean fclean re norminette
