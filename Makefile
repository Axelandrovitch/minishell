# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 10:26:21 by dcampas-          #+#    #+#              #
#    Updated: 2025/04/29 17:18:26 by dcampas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
READLINE = -lreadline

#libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)

SRC =	src/main.c\
		src/parsing/token.c\
		src/parsing/aux_token.c\
		src/parsing/parse.c \
		src/environment.c\
		src/builtins/builtin_simple.c\
		src/builtins/builtin_env.c\
		src/builtins/execute.c \
		src/builtins/aux_builtins.c \
		src/builtins/builtin_cd.c \
		src/builtins/builtin_export.c


OBJ = $(SRC:.c=.o)


all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME) $(READLINE)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
