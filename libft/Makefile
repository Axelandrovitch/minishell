# Nombre de la librería
NAME := libft.a

# Compilador y flags
CC := cc
CFLAGS := -Wall -Wextra -Werror

# Directorios
SRC_DIR := src
OBJ_DIR := obj
INC_DIR := include

# Lista de archivos fuente (añade aquí los tuyos)
SRC := \
	$(SRC_DIR)/ft_is/ft_isalpha.c \
	$(SRC_DIR)/ft_is/ft_isdigit.c \
	$(SRC_DIR)/ft_is/ft_isalnum.c \
	$(SRC_DIR)/ft_is/ft_isascii.c \
	$(SRC_DIR)/ft_is/ft_isprint.c \
	$(SRC_DIR)/ft_mem/ft_memset.c \
	$(SRC_DIR)/ft_mem/ft_bzero.c \
	$(SRC_DIR)/ft_mem/ft_memcpy.c \
	$(SRC_DIR)/ft_mem/ft_memmove.c \
	$(SRC_DIR)/ft_str/ft_strlen.c \
	$(SRC_DIR)/ft_str/ft_strlcpy.c \
	$(SRC_DIR)/ft_str/ft_strdup.c \
	$(SRC_DIR)/ft_str/ft_strndup.c \
	$(SRC_DIR)/ft_str/ft_strchr.c \
	$(SRC_DIR)/ft_str/ft_strrchr.c \
	$(SRC_DIR)/ft_str/ft_strncmp.c \
	$(SRC_DIR)/ft_str/ft_strcmp.c \
	$(SRC_DIR)/ft_str/ft_strncpy.c \
	$(SRC_DIR)/ft_str/ft_strnstr.c \
	$(SRC_DIR)/ft_str/ft_strlcat.c \
	$(SRC_DIR)/ft_put/ft_putchar_fd.c \
	$(SRC_DIR)/ft_mem/ft_memchr.c \
	$(SRC_DIR)/ft_mem/ft_memcmp.c \
	$(SRC_DIR)/ft_str/ft_substr.c \
	$(SRC_DIR)/ft_str/ft_strjoin.c \
	$(SRC_DIR)/ft_str/ft_putstr_fd.c \
	$(SRC_DIR)/ft_put/ft_putendl_fd.c \
	$(SRC_DIR)/ft_str/ft_strtrim.c \
	$(SRC_DIR)/ft_str/ft_split.c \
	$(SRC_DIR)/ft_to/ft_atoi.c \
	$(SRC_DIR)/ft_to/ft_itoa.c \
	$(SRC_DIR)/ft_to/ft_atol.c \
	$(SRC_DIR)/ft_mem/ft_calloc.c \
	$(SRC_DIR)/ft_to/ft_toupper.c \
	$(SRC_DIR)/ft_to/ft_tolower.c \

# Archivos objeto
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Regla principal
all: $(NAME)

# Cómo crear la librería
$(NAME): $(OBJ)
	ar rcs $@ $^

# Cómo compilar los .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

# Limpiar los objetos
clean:
	rm -rf $(OBJ_DIR)

# Limpiar todo
fclean: clean
	rm -f $(NAME)

# Recompilar
re: fclean all

.PHONY: all clean fclean re
