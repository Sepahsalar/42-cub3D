# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 15:48:51 by asohrabi          #+#    #+#              #
#    Updated: 2024/07/19 16:04:00 by nnourine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors for echo
COLOR = \033[0;34m
RESET_COLOR = \033[0m

# Project name
NAME = cub3D

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRCDIR = src/c_files
INCDIR = include
OBJDIR = obj

# Libraries
LIBMLX = lib/MLX42
LIBFT = lib/libft
LIB_BREW = /Users/${USER}/.brew/Cellar/glfw/3.4/lib

# Header files
HEADERS	= -I $(INCDIR) -I $(LIBMLX)/include

# Library flags
LIBFT_FLAGS = -L$(LIBFT) -lft
LMX_FLAGS = -L$(LIBMLX)/build -L$(LIB_BREW) -lmlx42 -ldl -pthread -lglfw -lm
LIBS_FLAGS = $(LIBFT_FLAGS) $(LMX_FLAGS)

# Source files
SRCS = $(SRCDIR)/calculate_character_size.c  \
       $(SRCDIR)/check_exit.c  \
       $(SRCDIR)/check_near_wall.c  \
       $(SRCDIR)/check_reach_to_collectible.c  \
       $(SRCDIR)/check_with_wall_instance.c  \
       $(SRCDIR)/create_background.c  \
       $(SRCDIR)/create_elements.c  \
       $(SRCDIR)/create_window_elements.c  \
       $(SRCDIR)/escape_key.c  \
       $(SRCDIR)/exit.c  \
       $(SRCDIR)/map_to_instance.c  \
       $(SRCDIR)/map_to_instance_resize.c  \
       $(SRCDIR)/press_key.c  \
       $(SRCDIR)/point_data_start.c  \
       $(SRCDIR)/resize.c  \
       $(SRCDIR)/player.c \
       $(SRCDIR)/start_position.c \
       $(SRCDIR)/touch_cell.c \
       $(SRCDIR)/check_ber.c \
       $(SRCDIR)/map_data.c \
       $(SRCDIR)/check_side_wall.c \
       $(SRCDIR)/check_rectangular.c \
       $(SRCDIR)/check_character_number.c \
       $(SRCDIR)/check_valid_path.c \
       $(SRCDIR)/validate_map.c \
       $(SRCDIR)/so_long.c

# Object files
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Targets
.PHONY: all clean fclean re

# Default target
all: $(NAME)

# Build target
$(NAME): $(OBJS)
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@make -C $(LIBMLX)/build -j4
	@make -C $(LIBFT)
	@$(CC) $(OBJS) $(CFLAGS) $(LIBS_FLAGS) $(HEADERS) -o $(NAME)
	@echo "$(COLOR)Compiling and linking: done$(RESET_COLOR)"

# Object file compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

# Clean target
clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT) clean
	@rm -rf $(LIBMLX)/build

# Full clean target
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@echo "$(COLOR)Full clean: done$(RESET_COLOR)"

# Rebuild target
re: fclean all
