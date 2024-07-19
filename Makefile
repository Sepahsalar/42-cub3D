# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 15:48:51 by nnourine          #+#    #+#              #
#    Updated: 2024/07/19 11:48:48 by nnourine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color
COLOR = \033[0;34m
RESET_COLOR = \033[0m

# Executable name
NAME = cub3D

# Compiler and flags
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
GENERAL_LIB_FLAGS = -L$(LIBFT) -L$(LIBPRINT) -lft -lftprintf
MATH = -lm
LMX_FLAGS = -L$(LIBMLX)/build -lmlx42 -ldl -pthread -lm -lglfw

# Directories
SRCDIR = src/c_files
INCDIR = include
LIBMLX = lib/MLX42
LMXINC = $(LIBMLX)/include
LIBFT = lib/libft
LIBPRINT = lib/ft_printf

# Files
SRCS = $(SRCDIR)/cub3D.c
OBJS = $(SRCS:.c=.o)

# Phony targets
.PHONY: all clean fclean re clone_mlx

# Default target
all: $(LIBMLX)/build $(NAME)

# Clone MLX42 repository
clone_mlx:
	git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX)

# Build MLX42
$(LIBMLX)/build: $(LIBMLX)
	cmake -B $(LIBMLX)/build $(LIBMLX)
	cmake --build $(LIBMLX)/build -j4

# Linking
$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) -C $(LIBPRINT)
	@$(CC) $(CFLAGS) $(MATH) $(GENERAL_LIB_FLAGS) $(LMX_FLAGS) $(OBJS) -o $@
	@echo "$(COLOR)Compiling and linking: done$(RESET_COLOR)"

# Compiling
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -I$(INCDIR) -I$(LMXINC) -c $< -o $@

# Clean-up
clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBPRINT) clean
	@$(RM) -r $(LIBMLX)/build
	@echo "$(COLOR)Clean-up: done$(RESET_COLOR)"

# Full clean
fclean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBPRINT) clean
	@$(RM) -r $(LIBMLX)/build
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBPRINT) fclean
	@echo "$(COLOR)Full clean: done$(RESET_COLOR)"

# Recompile
re: fclean all
