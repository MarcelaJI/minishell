# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 11:06:40 by ingjimen          #+#    #+#              #
#    Updated: 2025/06/26 10:47:44 by ingjimen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -Isrc -Ilibft/includes

SRC = src/main.c \
	  src/parsing/tokenizer.c src/parsing/tokenizer_utils.c src/parsing/quotes.c \
	  src/parsing/parsing.c src/parsing/parsing_utils.c src/parsing/fix_input.c \
	  src/parsing/env.c src/parsing/env_vars.c src/parsing/env_vars_utils.c \
	  src/utils/utils.c src/utils/error.c src/utils/list_utils.c src/utils/list_utils_2.c

OBJ = $(SRC:.c=.o)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

.PHONY: all clean fclean re

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) > /dev/null

$(NAME): $(OBJ)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@printf "\033[34m"  # amarillo
	@echo "  __  __ _____ _   _ _____  _____ _    _ ______ _      _      "
	@echo " |  \\/  |_   _| \\ | |_   _|/ ____| |  | |  ____| |    | |     "
	@echo " | \\  / | | | |  \\| | | | | (___ | |__| | |__  | |    | |     "
	@echo " | |\\/| | | | | . ' | | |  \\___ \\|  __  |  __| | |    | |     "
	@echo " | |  | |_| |_| |\\  |_| |_ ____) | |  | | |____| |____| |____ "
	@echo " |_|  |_|_____|_| \\_|_____|_____/|_|  |_|______|______|______|"
	@printf "\033[33m" "By ingjimen- & iranieri\n"
	@echo ""
	@printf "\033[0m"  # reset color

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR) > /dev/null

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) > /dev/null

re: fclean all
