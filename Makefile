# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 15:48:51 by asohrabi          #+#    #+#              #
#    Updated: 2024/07/25 15:57:40 by asohrabi         ###   ########.fr        #
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
SRCS = $(SRCDIR)/create_loc.c \
		$(SRCDIR)/create_render.c \
		$(SRCDIR)/main.c  \
		$(SRCDIR)/map_parser.c  \
		$(SRCDIR)/map_parser_utils.c \
		$(SRCDIR)/termiante.c \

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
#	@git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX)
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

# Clean target
clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJDIR)
	@make -C $(LIBFT) clean
	@rm -rf $(LIBMLX)/build
#	@rm -rf $(LIBMLX)

# Full clean target
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@echo "$(COLOR)Full clean: done$(RESET_COLOR)"

# Rebuild target
re: fclean all
