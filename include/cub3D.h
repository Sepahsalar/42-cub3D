/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:36:16 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/12 14:53:06 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>  // For malloc, free, exit
# include <string.h>  // For strerror
# include <unistd.h>  // For open, close, read, write
# include <fcntl.h>   // For file control options
# include <errno.h>   // For errno
# include <stdio.h>   // For printf
# include <math.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

// # define START_IMAGE_SIZE 100
// # define MIN_IMAGE_SIZE 10
// # define MAX_MONITOR_USAGE 0.95

# define FULL_CIRCLE_DEGREES 360
# define VAOV 120.0
# define HAOV 180.0
# define WINDOW_HEIGHT 600
# define WINDOW_WIDTH 900
# define HEIGHT_INTERVAL (VAOV / WINDOW_HEIGHT)
# define WIDTH_INTERVAL (HAOV / WINDOW_WIDTH)
# define TURN_INTERVAL 1
# define NLOOP WINDOW_WIDTH
# define PERSON 2.0
# define WALL 3.0
# define BRICKS_IN_H 1
#define EPSILON 0.00001

typedef struct s_loc
{
	int				x;
	int				y;
	char			c;
	int				x0;
	int				y0;
	int				x1;
	int				y1;
	double			x_mid;
	double			y_mid;
	double			sx;
	double			sy;
	double			ex;
	double			ey;
	double			wx;
	double			wy;
	double			nx;
	double			ny;
	struct s_loc	*next;
	struct s_loc	*previous;
}					t_loc;

typedef struct s_render
{
	double	ceil_height;
	double	floor_height;
	double	wall_height;
	char	wall_texture;
	int		x;
}			t_render;

typedef struct s_map
{
	char	*north;
	char	*south;
	char 	*west;
	char	*east;
	char	*f;
	char	*c;
	t_loc	*start;
}			t_map;

typedef struct s_elem
{
	mlx_image_t	*north;
	mlx_image_t	*west;
	mlx_image_t	*south;
	mlx_image_t	*east;
	mlx_image_t	*f;
	mlx_image_t	*c;
}				t_elem;

typedef struct s_image
{
	mlx_image_t		*image;
	struct s_data	*next;
}					t_image;

typedef struct s_strip
{
	int				x;
	char			wall;
	double			wall_h;
	double			ceil_h;
	double			floor_h;
	int				wall_length;
	int				index;
	struct s_strip	*previous;
	struct s_strip	*next;
}					t_strip;

typedef struct s_possible
{
	t_loc				*loc;
	double				sn_winner_distance;
	double				ew_winner_distance;
	char				sn_winner_texture;
	char				ew_winner_texture;
	double				sn_winner_x;
	double				sn_winner_y;
	double				ew_winner_x;
	double				ew_winner_y;
	struct s_possible	*previous;
	struct s_possible	*next;
}						t_possible;

typedef struct s_winner
{
	t_possible	*pos;
	char		texture;
}				t_winner;

typedef struct s_range
{
	int	x_min;
	int	x_max;
	int	y_min;
	int y_max;
}		t_range;

typedef struct s_all
{
	t_map	*map;
	int		floor_color;
	int 	ceil_color;
	double	x;
	double	y;
	double	angle;
	double	left_distance;
	double	right_distance;
	int		distance_flag;
	t_possible *possible;
	double 	map_width;
	double 	map_height;
	double 	max_distance;
	int		fd;
	char	*strmap;
	char	*argv;
	mlx_t	*window;
	t_strip	*strip;
	mlx_image_t	*image;
	mlx_image_t	*north;
	mlx_image_t	*west;
	mlx_image_t	*south;
	mlx_image_t	*east;
}			t_all;

int			color(int r, int g, int b, int a);
t_map		*map_parser(t_all *all);
void		terminate(t_all *all, int status);
void		check_failure(int input1, void *input2, int type, t_all *all);
void		reader(t_all *all);
void		create_loc(t_all *all);
t_loc		*create_loc_node(char temp, int x, int y);
t_loc		*clean_loc(t_loc *first);
void		init_strip(t_all *all, t_render data_render);
void 		fill_index_strip(t_all *all);
void 		fill_length_strip(t_all *all);
void		clean_strip(t_all *all);
mlx_image_t	*image_maker(t_all *all, char type);
int			color_maker(t_all *all, char type);
void		strip_to_image(t_all *all);
void		press_key(mlx_key_data_t keydata, void *param);
void 		render(t_all *all);
double 		under_full_circle(double angle);
t_possible	*clean_possibility(t_possible *first);
void		create_possibility(t_all *all, t_range range);
void 		find_winner_surface(t_all *all);
void 		ignore_inside_surface(t_all *all);
int			game_size(t_all *all, char c);
double 		max_distance(t_all *all);

#endif // CUB3D_H
