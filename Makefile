# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/24 11:06:40 by ingjimen          #+#    #+#              #
#    Updated: 2025/06/24 14:40:14 by ingjimen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = src/minishell.h -Ilibft/includes

SRC = src/main.c src/parsing/tokenizer.c src/parsing/tokenizer_utils.c \
		src/parsing/parsing.c src/parsing_utils.c src/parsing/fix_input.c \
		src/utils/utils.c src/utils/error.c src/utils/list_utils.c src/utils/list_utils_2.c  \
		
OBJ = $(SRC:.c=.o)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

GREEN = \033[0;32m
RED = \033[1;31m
BLUE_UNDER = \033[1;34m
BLUE = \033[0;34m
YELLOW = \033[0;33m
CYAN = \033[1;36m
MAGENTA = \033[0;35m
WHITE = \033[1;37m
WHITE_RED_BG = \033[0;41;37m
YELLOW_UNDER = \033[1;4;33m
NC = \033[0m

all: $(LIBFT) $(NAME)

$(LIBFT):
	@echo "$(YELLOW)Compiling $(NAME)$(NC)"
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@echo "$(YELLOW)Compiling $(NAME)$(NC)"
	$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIBFT) -o $(NAME) -lreadline


clean:
	@echo "$(RED)Removing .o files$(NC)"
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@echo "$(RED)Removing executable$(NC)"
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all
