# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcampas- <dcampas-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/10 16:06:42 by ahetru            #+#    #+#              #
#    Updated: 2025/06/12 14:38:51 by dcampas-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
CC := cc
CFLAGS := -Wall -Wextra -Werror -fsanitize=address
READLINE := -lreadline

SRC_DIR := src
OBJ_DIR := obj
INC_DIR := inc
LIBFT_DIR := libft

INCLUDES := -I$(INC_DIR) -I$(LIBFT_DIR)
LIBFT := $(LIBFT_DIR)/libft.a

SRC := \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/lexer/token.c \
	$(SRC_DIR)/lexer/lexer.c \
	$(SRC_DIR)/lexer/handle_quotes.c \
	$(SRC_DIR)/lexer/lexer_utils.c \
	$(SRC_DIR)/lexer/aux_token.c \
	$(SRC_DIR)/parser/expand_variables.c \
	$(SRC_DIR)/parser/expand_variables_utils.c \
	$(SRC_DIR)/parser/expand_variables_utils2.c \
	$(SRC_DIR)/parser/parse_pipeline.c \
	$(SRC_DIR)/parser/parse_command_blocks.c \
	$(SRC_DIR)/parser/parser_utils.c \
	$(SRC_DIR)/execution/execute_pipeline.c \
	$(SRC_DIR)/execution/execute_commands.c \
	$(SRC_DIR)/execution/execute_external_command.c \
	$(SRC_DIR)/execution/execution_utils.c \
	$(SRC_DIR)/execution/print_errors.c \
	$(SRC_DIR)/execution/free.c \
	$(SRC_DIR)/execution/handle_redirections.c \
	$(SRC_DIR)/execution/handle_heredoc.c \
	$(SRC_DIR)/builtins/builtin_simple.c \
	$(SRC_DIR)/builtins/builtin_cd.c \
	$(SRC_DIR)/builtins/cd_utils.c \
	$(SRC_DIR)/builtins/builtin_echo.c \
	$(SRC_DIR)/builtins/builtin_env.c \
	$(SRC_DIR)/environment/environment.c \
	$(SRC_DIR)/environment/env_utils.c \
	$(SRC_DIR)/environment/env_utils2.c \
	$(SRC_DIR)/builtins/builtin_export.c \
	$(SRC_DIR)/builtins/export_utils.c \
	$(SRC_DIR)/builtins/execute.c \
	$(SRC_DIR)/builtins/builtin_unset.c \
	$(SRC_DIR)/signals/signals.c \

LIBFT_SRC := \
	$(LIBFT_DIR)/src/ft_is/ft_isalpha.c \
	$(LIBFT_DIR)/src/ft_is/ft_isdigit.c \
	$(LIBFT_DIR)/src/ft_is/ft_isalnum.c \
	$(LIBFT_DIR)/src/ft_is/ft_isascii.c \
	$(LIBFT_DIR)/src/ft_is/ft_isprint.c \
	$(LIBFT_DIR)/src/ft_mem/ft_memset.c \
	$(LIBFT_DIR)/src/ft_mem/ft_bzero.c \
	$(LIBFT_DIR)/src/ft_mem/ft_memcpy.c \
	$(LIBFT_DIR)/src/ft_mem/ft_memmove.c \
	$(LIBFT_DIR)/src/ft_str/ft_strlen.c \
	$(LIBFT_DIR)/src/ft_str/ft_strlcpy.c \
	$(LIBFT_DIR)/src/ft_str/ft_strdup.c \
	$(LIBFT_DIR)/src/ft_str/ft_strndup.c \
	$(LIBFT_DIR)/src/ft_str/ft_strchr.c \
	$(LIBFT_DIR)/src/ft_str/ft_strrchr.c \
	$(LIBFT_DIR)/src/ft_str/ft_strncmp.c \
	$(LIBFT_DIR)/src/ft_str/ft_strcmp.c \
	$(LIBFT_DIR)/src/ft_str/ft_strncpy.c \
	$(LIBFT_DIR)/src/ft_str/ft_strnstr.c \
	$(LIBFT_DIR)/src/ft_str/ft_strlcat.c \
	$(LIBFT_DIR)/src/ft_put/ft_putchar_fd.c \
	$(LIBFT_DIR)/src/ft_mem/ft_memchr.c \
	$(LIBFT_DIR)/src/ft_mem/ft_memcmp.c \
	$(LIBFT_DIR)/src/ft_str/ft_substr.c \
	$(LIBFT_DIR)/src/ft_str/ft_strjoin.c \
	$(LIBFT_DIR)/src/ft_str/ft_putstr_fd.c \
	$(LIBFT_DIR)/src/ft_put/ft_putendl_fd.c \
	$(LIBFT_DIR)/src/ft_str/ft_strtrim.c \
	$(LIBFT_DIR)/src/ft_str/ft_split.c \
	$(LIBFT_DIR)/src/ft_to/ft_atoi.c \
	$(LIBFT_DIR)/src/ft_to/ft_itoa.c \
	$(LIBFT_DIR)/src/ft_to/ft_atol.c \
	$(LIBFT_DIR)/src/ft_mem/ft_calloc.c \
	$(LIBFT_DIR)/src/ft_to/ft_toupper.c \
	$(LIBFT_DIR)/src/ft_to/ft_tolower.c

	
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(LIBFT): $(LIBFT_SRC) 
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT) Makefile minishell.h $(LIBFT_DIR)/Makefile $(LIBFT_DIR)/inc/libft.h
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME) $(READLINE)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
