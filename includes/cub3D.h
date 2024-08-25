/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nima <nnourine@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:36:16 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/25 11:30:41 by nima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <stdio.h> /////

# define PLAYER_PATH "./textures/player1.png"
# define GUN_PATH "./textures/gun7.png"
# define BLAST_PATH "./textures/blast1.png"

# define VAOV 90.0
# define HAOV 60.0
# define PERSON 2.0
# define WALL 4.0
# define EPSILON 0.00001
// # define DISTANCE_FROM_WALL 1.5
# define MIN_CALCULATED_DISTANCE 0.5
# define MINIMAP_SIDE 220
# define MINIMAP_COVERAGE 10
# define MAX_NODE 10001
# define BUFFER_SIZE 1000000
# define RENDER_INTERVAL 5
# define TURN_INTERVAL 18
# define FULL_CIRCLE_DEGREES 360
# define MINIMAP_PADDING 28
# define WINDOW_HEIGHT 1000
# define WINDOW_WIDTH 1000
# define START_GUN_X 610
# define START_GUN_Y 800
# define END_GUN_Y 700
# define START_BLAST_X 550
# define START_BLAST_Y 730
// # define START_GUN_X 200
// # define START_GUN_Y 850
// # define END_GUN_Y 800
// # define START_BLAST_X 350
// # define START_BLAST_Y 775
// # define WINDOW_WIDTH 900
// # define START_GUN_X 650
// # define START_GUN_Y 730
// # define END_GUN_Y 700
// # define START_BLAST_X 630
// # define START_BLAST_Y 780

typedef struct s_loc
{
	int				x;
	int				y;
	char			c;
	double			sx;
	double			sy;
	double			ex;
	double			ey;
	double			wx;
	double			wy;
	double			nx;
	double			ny;
	int				wet;
	double			sn_winner_distance;
	double			ew_winner_distance;
	char			sn_winner_texture;
	char			ew_winner_texture;
	double			sn_winner_x;
	double			sn_winner_y;
	double			ew_winner_x;
	double			ew_winner_y;
	int				consider;
	struct s_loc	*next;
	struct s_loc	*previous;
}					t_loc;

typedef struct s_render
{
	double			ceil_height;
	double			floor_height;
	double			wall_height;
	double 			fictional_wall_height;
	char			wall_texture;
	int				x;
	int				x_wall;
	int				y_wall;
	double			x_winner;
	double			y_winner;
	double			x_intersection;
	double			y_intersection;
}					t_render;

typedef struct s_map
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*f;
	char			*c;
	t_loc			*start;
}					t_map;

typedef struct s_player
{
	mlx_image_t		*image;
	double			angle;
	struct s_player	*next;
}					t_player;

typedef struct s_strip
{
	int				x;
	char			wall;
	double			wall_h;
	double 			fictional_wall_height;
	double			ceil_h;
	double			floor_h;
	int				wall_length;
	int				index;
	int				x_wall;
	int				y_wall;
	double			x_winner;
	double			y_winner;
	double			x_intersection;
	double			y_intersection;
	int				nb_blocks;
	struct s_strip	*previous;
	struct s_strip	*next;
}					t_strip;

typedef struct s_winner
{
	t_loc			*pos;
	char			texture;
	double			x_winner;
	double			y_winner;
	double			x_intersection;
	double			y_intersection;
	double			intersection_distance;
}					t_winner;

typedef struct s_range
{
	int				x_min;
	int				x_max;
	int				y_min;
	int				y_max;
}					t_range;

typedef struct s_pixel_bricks
{
	int				x_in_resized_brick;
	int				y_in_resized_brick;
	int				y_in_wall;
	int				x_in_brick;
	int				y_in_brick;
	int				h_resized_brick;
	int				w_resized_brick;
}					t_pixel_bricks;

typedef struct s_current_wall
{
	char			wall;
	int				x_winner;
	int				y_winner;
	int				index;
}					t_current_wall;

typedef struct s_coordinate
{
	int				x;
	int				y;
	int				index;
}					t_coordinate;

typedef struct s_rotate
{
	int				i;
	int				j;
	int				x;
	int				y;
	int				new_x;
	int				new_y;
}					t_rotate;

typedef struct s_all
{
	t_map			*map;
	int				floor_color;
	int				ceil_color;
	double			x;
	double			y;
	double			angle;
	int				distance_flag;
	double			map_width;
	double			map_height;
	double			max_distance;
	int				fd;
	char			*strmap;
	char			*argv;
	int				index;
	int 			started_button;
	long long		start_time;
	long long		current_time;
	int				active_weapon;
	double			time1;
	double			time2;
	int				gun_used;
	int				animation_started;
	int				x_mouse;
	int				y_mouse;
	mlx_t			*window;
	t_strip			*strip;
	mlx_image_t		*image;
	mlx_image_t		*minimap;
	mlx_image_t		*gun;
	mlx_image_t		*knife;
	mlx_image_t		*blast;
	t_player		*player_image;
	mlx_image_t		*north;
	mlx_image_t		*west;
	mlx_image_t		*south;
	mlx_image_t		*east;
	mlx_image_t		*player_at_0;
}					t_all;

int					color(int r, int g, int b, int a);
t_map				*map_parser(t_all *all);
void				terminate(t_all *all, int status);
void				check_failure(int input1, void *input2, int type,
						t_all *all);
void				reader(t_all *all);
void				create_loc(t_all *all);
t_loc				*create_loc_node(char temp, int x, int y);
void 				remove_unnecessary_nodes(t_all *all);
t_loc				*clean_loc(t_loc *first);
void				init_strips(t_all *all, t_render data_render);
void				fill_index_strips(t_all *all);
void				fill_length_strips(t_all *all);
void				clean_strips(t_all *all);
mlx_image_t			*image_maker(t_all *all, char type);
int					color_maker(t_all *all, char type);
void				strip_to_image(t_all *all);
void				press_key(mlx_key_data_t keydata, void *param);
void				fill_strips(t_all *all);
double				under_full_circle(double angle);
void				find_winner_surface(t_all *all);
void				ignore_inside_surface(t_all *all);
int					game_size(t_all *all, char c);
double				max_distance(t_all *all);
void				update_strips(t_all *all);
void				clean_2d_char_array(char **array);
void				temp_movment225(double *new_x, double *new_y, char c);
void				temp_movment135(double *new_x, double *new_y, char c);
void				temp_movment45(double *new_x, double *new_y, char c);
void				temp_movment315(double *new_x, double *new_y, char c);
void				conditional_move(t_all *all, double new_x, double new_y);
int					is_wall_there(t_all *all, int x, int y);
int					get_pixel(mlx_image_t *image, int i, int j);
char				*custom_strdup(t_all *all, char *found, char *str);
void				remove_white_space(t_all *all);
void				check_valid_color(t_all *all, char type);
double				ft_tan(double a);
double				ft_cos(double a);
double				ft_sin(double a);
double				distance(double x1, double y1, double x2, double y2);
int					same(double d1, double d2);
double				height(double distance, char c);
t_winner			calculate_distance(t_all *all, t_winner final,
						double ray_angle);
int					check_map_format(char *str);
double				find_x(double angle, double x_player, double y_player,
						double y_target);
double				find_y(double angle, double x_player, double y_player,
						double x_target);
double				min_x(double x_player, double angle);
double				max_x(double x_player, int x_game_size, double angle);
double				min_y(double y_player, double angle);
double				max_y(double y_player, int y_game_size, double angle);
t_winner			find_winner(t_all *all, double ray_angle);
t_all				*init_all(char **argv);
int					find_min_x(t_all *all, int y);
int					find_max_x(t_all *all, int y);
int					find_min_y(t_all *all, int x);
int					find_max_y(t_all *all, int x);
void				compare_adjacent_walls(t_loc *temp1, t_loc *temp2);
void				link_new_node(t_all *all, t_loc *new, t_loc *old);
void				update_coordinate(t_coordinate *coordinate, char *temp);
t_strip				*last_node_strips(t_strip *node);
t_strip				*last_wall_node(t_strip *node);
t_strip				*first_wall_node(t_strip *node);
t_strip				*create_strips_node(t_render data_render);
void				ignore_upper_wall(t_all *all, t_loc *loc);
void				ignore_lower_wall(t_all *all, t_loc *loc);
void				ignore_left_wall(t_all *all, t_loc *loc);
void				ignore_right_wall(t_all *all, t_loc *loc);
void				reset_loc(t_all *all);
void				find_visible_surface(t_all *all, t_range range);
t_winner			find_specific_intersection(t_all *all, double ray_angle,
						char flag);
t_winner			set_final_x_y_winner(t_winner final);
t_winner			set_final_pos_and_texture(t_winner final, t_loc *temp_pos,
						char type);
t_winner			find_general_intersection(t_all *all, double ray_angle);
void				south_wins(t_all *all, t_loc *temp);
void				east_wins(t_all *all, t_loc *temp);
void				north_wins(t_all *all, t_loc *temp);
void				west_wins(t_all *all, t_loc *temp);
void				create_minimap(t_all *all);
void				create_player_image(t_all *all);
void				enable_correct_player(t_all *all);
void				check_empty_map(t_all *all, char *str, char *error);
long long			ft_timestamp_milis(t_all *all);
void				mouse(double xpos, double ypos, void* param);
void				clean_player_image(t_all *all);
void				click(mouse_key_t button, action_t action, modifier_key_t mods, void* param);
void				animation(void *param);

#endif // CUB3D_H
