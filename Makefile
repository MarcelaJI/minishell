# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iranieri <iranieri@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 11:06:40 by ingjimen          #+#    #+#              #
#    Updated: 2025/07/06 21:07:16 by iranieri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror

READLINE_INCLUDE = -I/opt/homebrew/opt/readline/include

READLINE_LIB = -L/opt/homebrew/opt/readline/lib -lreadline

INC = -Isrc -Ilibft/includes $(READLINE_INCLUDE)

SRC = src/init/minishell.c \
          src/parsing/tokenizer.c src/parsing/tokenizer_utils.c src/parsing/quotes.c \
          src/parsing/parsing.c src/parsing/parsing_utils.c src/parsing/fix_input.c \
          src/parsing/env.c src/parsing/env_vars.c src/parsing/env_vars_utils.c \
          src/init/env_init.c src/init/take_input.c \
          src/utils/utils.c src/utils/error.c src/utils/list_utils.c src/utils/list_utils_2.c \
          src/execution/execution.c src/execution/execution_utils.c src/execution/execution_utils_2.c src/execution/heredoc.c \
          src/execution/open_files.c src/execution/redirection.c src/execution/signals.c \
          src/builtin/builtin.c src/builtin/ft_cd.c src/builtin/ft_echo.c \
          src/builtin/ft_env_unset.c src/builtin/ft_exit.c src/builtin/ft_export.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

GREEN = \033[0;32m
RED = \033[1;31m
BLUE_UNDER = \033[1;34m
YELLOW = \033[0;33m
CYAN = \033[1;36m
MAGENTA = \033[0;35m
WHITE = \033[1;37m
WHITE_RED_BG = \033[0;41;37m
YELLOW_UNDER = \033[1;4;33m
NC = \033[0m

.PHONY: all clean fclean re

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null

$(NAME): $(OBJ)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) > /dev/null
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) $(READLINE_LIB) -o $(NAME) > /dev/null
	@printf "$(CYAN)"
	@echo "      _          _ _           _ "
	@echo "     | |        | | |         (_)"
	@echo "  ___| |__   ___| | |_ __ ___  _ "
	@echo " / __| '_ \\ / _ \\ | | '_ \` _ \\| |"
	@echo " \\__ \\ | | |  __/ | | | | | | | |"
	@echo " |___/_| |_|\\___|_|_|_| |_| |_|_|"
	@printf "$(YELLOW)      By ingjimen & iranieri\n"
	@echo ""

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@ > /dev/null

clean:
	@rm -f $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR) > /dev/null

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null

re: fclean all


