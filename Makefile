# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nima <nnourine@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 15:48:51 by asohrabi          #+#    #+#              #
#    Updated: 2024/08/25 15:32:32 by nima             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors for echo
COLOR = \033[0;34m
RESET_COLOR = \033[0m

# Project name
NAME = cub3D

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRCDIR = srcs
INCDIR = includes
OBJDIR = objs

# Libraries
LIBMLX = libs/MLX42
LIBFT = libs/libft
LIB_BREW = /Users/${USER}/.brew/Cellar/glfw/3.4/lib

# Header files
HEADERS	= -I $(INCDIR) -I $(LIBMLX)/include

# Library flags
LIBFT_FLAGS = -L$(LIBFT) -lft
LMX_FLAGS = -L$(LIBMLX)/build -L$(LIB_BREW) -lmlx42 -ldl -pthread -lglfw -lm
LIBS_FLAGS = $(LIBFT_FLAGS) $(LMX_FLAGS)

# Source files
SRCS = 	$(SRCDIR)/acceptable_range.c \
		$(SRCDIR)/calculate_distance.c \
		$(SRCDIR)/compare_adjacent_walls.c\
		$(SRCDIR)/create_loc.c \
		$(SRCDIR)/create_loc_utils.c \
		$(SRCDIR)/create_loc_utils2.c \
		$(SRCDIR)/fill_index_strips.c \
		$(SRCDIR)/fill_strips.c \
		$(SRCDIR)/fill_strips_utils.c \
		$(SRCDIR)/fill_strips_utils2.c \
		$(SRCDIR)/find_coordinate_ranges.c \
		$(SRCDIR)/find_general_intersection.c \
		$(SRCDIR)/find_specific_intersection.c \
		$(SRCDIR)/find_winner_surface.c \
		$(SRCDIR)/find_winner_surface_utils.c \
		$(SRCDIR)/find_winner.c \
		$(SRCDIR)/ft_math.c \
		$(SRCDIR)/ignore_inside_surface.c \
		$(SRCDIR)/ignore_inside_surface_utils.c \
		$(SRCDIR)/init_all.c \
		$(SRCDIR)/loc_visibility.c \
		$(SRCDIR)/main.c  \
		$(SRCDIR)/map_parser.c  \
		$(SRCDIR)/map_parser_color.c \
		$(SRCDIR)/map_parser_utils.c \
		$(SRCDIR)/minimap.c \
		$(SRCDIR)/move.c \
		$(SRCDIR)/press_key.c \
		$(SRCDIR)/strip_to_image.c \
		$(SRCDIR)/termiante.c \
		$(SRCDIR)/time.c \
		$(SRCDIR)/utils.c \
		$(SRCDIR)/utils2.c

# Object files
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Targets
.PHONY: all clean fclean re

# Default target
all: clone_mlx42 $(NAME)

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

# Clone the external repo if not already cloned
clone_mlx42:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "$(COLOR)Cloning MLX42 repository...$(RESET_COLOR)"; \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi

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
	@rm -rf $(LIBMLX)
	@echo "$(COLOR)Full clean: done$(RESET_COLOR)"

# Rebuild target
re: fclean all
