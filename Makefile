# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/27 15:48:51 by asohrabi          #+#    #+#              #
#    Updated: 2024/08/29 14:59:11 by asohrabi         ###   ########.fr        #
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
INCDIR = includes
SRCSDIR = srcs
SRCSDIR_BONUS = srcs_bonus
OBJSDIR = objs
OBJSDIR_BONUS = objs_bonus

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
MANDATORY_FILES = acceptable_range.c \
					calculate_distance.c compare_adjacent_walls.c \
					create_loc.c create_loc_utils.c \
					create_loc_utils2.c fill_index_strips.c \
					fill_strips.c fill_strips_utils.c \
					fill_strips_utils2.c find_coordinate_ranges.c \
					find_general_intersection.c find_specific_intersection.c \
					find_winner_surface.c find_winner_surface_utils.c \
					find_winner.c flood_map.c flood_map_utils.c \
					ft_math.c ignore_inside_surface.c \
					ignore_inside_surface_utils.c init_all.c keyboard.c \
					loc_visibility.c main.c map_parser.c \
					map_parser_color.c map_parser_utils.c map_parser_utils2.c \
					move.c move_utils.c turn.c strip_to_image.c \
					terminate.c time.c utils.c utils2.c

BONUS_FILES = acceptable_range_bonus.c animation_bonus.c animation_utils_bonus.c \
					calculate_distance_bonus.c compare_adjacent_walls_bonus.c \
					create_loc_bonus.c create_loc_utils_bonus.c \
					create_loc_utils2_bonus.c fill_index_strips_bonus.c \
					fill_strips_bonus.c fill_strips_utils_bonus.c \
					fill_strips_utils2_bonus.c find_coordinate_ranges_bonus.c \
					find_general_intersection_bonus.c find_specific_intersection_bonus.c \
					find_winner_surface_bonus.c find_winner_surface_utils_bonus.c \
					find_winner_bonus.c flood_map_bonus.c flood_map_utils_bonus.c \
					ft_math_bonus.c ignore_inside_surface_bonus.c \
					ignore_inside_surface_utils_bonus.c init_all_bonus.c keyboard_bonus.c \
					loc_visibility_bonus.c main_bonus.c  map_parser_bonus.c \
					map_parser_color_bonus.c map_parser_utils_bonus.c map_parser_utils2_bonus.c \
					minimap_bonus.c minimap_player_bonus.c minimap_player2_bonus.c mouse_bonus.c \
					move_bonus.c move_utils_bonus.c turn_bonus.c strip_to_image_bonus.c \
					terminate_bonus.c time_bonus.c utils_bonus.c utils2_bonus.c

SRCS = $(addprefix srcs/, $(MANDATORY_FILES))

SRCS_BONUS = $(addprefix srcs_bonus/, $(BONUS_FILES))

# Object files
OBJS = $(SRCS:$(SRCSDIR)/%.c=$(OBJSDIR)/%.o)

OBJS_BONUS = $(SRCS_BONUS:$(SRCSDIR_BONUS)/%.c=$(OBJSDIR_BONUS)/%.o) 

# Targets
.PHONY: all clean fclean re bonus

# Default target
all: clone_mlx42 $(NAME)

# Build target
$(NAME): $(OBJS)
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@make -C $(LIBMLX)/build -j4
	@make -C $(LIBFT)
	@rm -f .bonus
	@rm -rf $(OBJSDIR_BONUS)
	@$(CC) $(OBJS) $(CFLAGS) $(LIBS_FLAGS) $(HEADERS) -o $(NAME)
	@echo "$(COLOR)Compiling and linking: done$(RESET_COLOR)"

# Object file compilation
$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(OBJSDIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(OBJSDIR_BONUS)/%.o: $(SRCSDIR_BONUS)/%.c
	@mkdir -p $(OBJSDIR_BONUS)
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

.bonus: clone_mlx42 $(OBJS_BONUS)
	@cmake $(LIBMLX) -B $(LIBMLX)/build
	@make -C $(LIBMLX)/build -j4
	@make -C $(LIBFT)
	@rm -rf $(OBJSDIR)
	@$(CC) $(OBJS_BONUS) $(CFLAGS) $(LIBS_FLAGS) $(HEADERS) -o $(NAME)
	@touch .bonus

bonus: .bonus

# Clone the external repo if not already cloned
clone_mlx42:
	@if [ ! -d "$(LIBMLX)" ]; then \
		echo "$(COLOR)Cloning MLX42 repository...$(RESET_COLOR)"; \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX); \
	fi

delete_mlx:
	@rm -rf $(LIBMLX)

# Clean target
clean:
	@rm -rf $(OBJSDIR_BONUS)
	@rm -rf $(OBJSDIR)
	@rm -f .bonus
	@make -C $(LIBFT) clean
	@rm -rf $(LIBMLX)/build

# Full clean target
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean
	@echo "$(COLOR)Full clean: done$(RESET_COLOR)"

# Rebuild target
re: fclean all
