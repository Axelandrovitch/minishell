# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 10:26:21 by dcampas-          #+#    #+#              #
#    Updated: 2025/05/22 17:47:54 by dcampas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror -g
READLINE := -lreadline

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := inc
LIBFT_DIR := libft

INCLUDES := -I$(INC_DIR) -I$(LIBFT_DIR)
LIBFT := $(LIBFT_DIR)/libft.a

SRC := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parsing/token.c \
	$(SRC_DIR)/parsing/aux_token.c \
	$(SRC_DIR)/parsing/parse.c \
	$(SRC_DIR)/parsing/parser.c \
	$(SRC_DIR)/parsing/parser2.c \
	$(SRC_DIR)/execution/exec_commands.c \
	$(SRC_DIR)/execution/free.c \
	$(SRC_DIR)/execution/handle_redirections.c \
	$(SRC_DIR)/execution/handle_heredoc.c \
	$(SRC_DIR)/environment.c \
	$(SRC_DIR)/builtins/builtin_simple.c \
	$(SRC_DIR)/builtins/builtin_cd.c \
	$(SRC_DIR)/builtins/builtin_echo.c \
	$(SRC_DIR)/builtins/builtin_env.c \
	$(SRC_DIR)/builtins/env_utils.c \
	$(SRC_DIR)/builtins/builtin_export.c \
	$(SRC_DIR)/builtins/execute.c \
	$(SRC_DIR)/builtins/builtin_unset.c

OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME) $(READLINE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
