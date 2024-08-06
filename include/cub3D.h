/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:36:16 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/06 16:14:54 by asohrabi         ###   ########.fr       */
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

# define START_IMAGE_SIZE 100
# define MIN_IMAGE_SIZE 10
# define MAX_MONITOR_USAGE 0.95
# define FULL_CIRCLE_DEGREES 360
# define VAOV 120.0
# define HAOV 180.0
# define WINDOW_HEIGHT 600
# define WINDOW_WIDTH 900
# define HEIGHT_INTERVAL (VAOV / WINDOW_HEIGHT)
# define WIDTH_INTERVAL (HAOV / WINDOW_WIDTH)
#define NLOOP WINDOW_WIDTH
// # define WIDTH_INTERVAL 0.4
# define PERSON 1.5
# define WALL 3.0

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

typedef struct s_data
{
	int				x;
	int				y;
	mlx_image_t		*image;
	struct s_data	*previous;
	struct s_data	*next;
}					t_data;


typedef struct s_display
{
	t_data	*wall;
	t_data	*floor;
	t_data	*ceil;	
}			t_display;

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

typedef struct s_all
{
	t_map		*map;
	t_loc		*render;
	int			fd;
	char		*strmap;
	char		*argv;
	mlx_t		*window;
	t_elem		*elems;
	t_display	*display;
	t_strip		*strip;
}				t_all;

int		color(int r, int g, int b, int a);
t_map	*map_parser(t_all *all);
void	terminate(t_all *all, int status);
void	check_failure(int input1, void *input2, int type, t_all *all);
void	reader(t_all *all);
void	create_loc(t_all *all);
t_loc	*create_loc_node(char temp, int x, int y);
t_loc	*clean_loc(t_loc *first);
void	create_render(t_all *all, t_render data_render);
void	create_elements(t_all *all);
void	create_strip(t_all *all, t_render data_render);
void 	fill_index_strip(t_all *all);
void 	fill_length_strip(t_all *all);
void	clean_strip(t_strip *first);
void	strip_to_floor(t_all *all);
void	strip_to_wall(t_all *all);
void	strip_to_ceil(t_all *all);
t_data	*last_node_data(t_data *node);
void	create_instance(t_all *all);

#endif // CUB3D_H