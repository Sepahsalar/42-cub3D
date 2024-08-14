/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_to_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:13:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/14 16:47:22 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

mlx_image_t	*image_maker(t_all *all, char type)
{
	mlx_texture_t	*texture;
	mlx_image_t		*picture;
	char			*address;

	if (type == 'E')
		address = all->map->east;
	else if (type == 'W')
		address = all->map->west;
	else if (type == 'S')
		address = all->map->south;
	else
		address = all->map->north;
	texture = mlx_load_png(address);
	if (!texture)
		terminate(all, 1);
	picture = mlx_texture_to_image(all->window, texture);
	mlx_delete_texture(texture);
	if (!picture)
		terminate(all, 1);
	return (picture);
}

int	color(int r, int g, int b, int a)
{
	if (r >= 0 && g >= 0 && b >= 0 && a >= 0 && r <= 255 && g <= 255 && b <= 255
		&& a <= 255)
		return (r << 24 | g << 16 | b << 8 | a);
	if (r < 0)
		return (color(0, g, b, a));
	if (g < 0)
		return (color(r, 0, b, a));
	if (b < 0)
		return (color(r, g, 0, a));
	if (a < 0)
		return (color(r, g, b, 0));
	if (r > 255)
		return (color(255, g, b, a));
	if (g > 255)
		return (color(r, 255, b, a));
	if (b > 255)
		return (color(r, g, 255, a));
	return (color(r, g, b, 255));
}

void	clean_2d_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	color_maker(t_all *all, char type)
{
	char	*full_color;
	char	**split;
	int		int_color;

	if (type == 'f')
		full_color = all->map->f;
	else
		full_color = all->map->c;
	if (!full_color)
		terminate(all, 1);
	split = ft_split(full_color, ',');
	if (!split)
		terminate(all, 1);
	if (!split[3])
		int_color = color(ft_atoi(split[0]), ft_atoi(split[1]),
				ft_atoi(split[2]), 255);
	else
		int_color = color(ft_atoi(split[0]), ft_atoi(split[1]),
				ft_atoi(split[2]), ft_atoi(split[3]));
	clean_2d_char_array(split);
	return (int_color);
}
mlx_image_t	*choose_brick(t_all *all, char wall)
{
	if (wall == 'N')
		return (all->north);
	else if (wall == 'W')
		return (all->west);
	else if (wall == 'S')
		return (all->south);
	else
		return (all->east);
}

// int	dimension_resized_brick(t_strip *strip, char type)
// {
// 	if (type == 'h')
// 		return (round(strip->wall_h / BRICKS_IN_H));
// 	// return (round(strip->wall_h / (BRICKS_IN_H * WALL)));
// 	else
// 		return (round(strip->wall_length * BRICKS_IN_H / WALL));
// }

int	dimension_resized_brick(t_strip *strip, char type)
{
	if (type == 'h')
		return (round(strip->wall_h));
	else
		return (round(strip->wall_length / (2 * strip->nb_blocks)));
}

int	get_pixel(mlx_image_t *image, int i, int j)
{
	uint8_t	*pixel;

	pixel = image->pixels + 4 * (i + j * image->width);
	return (color(pixel[0], pixel[1], pixel[2], pixel[3]));
}

// int	get_pixel_from_brick(t_all *all, t_strip *strip, int y_in_window)
// {
// 	mlx_image_t	*brick;
// 	int			x_in_resized_brick;
// 	int			y_in_resized_brick;
// 	int			y_in_wall;
// 	int			x_in_brick;
// 	int			y_in_brick;
// 	int			h_resized_brick;
// 	int			w_resized_brick;

// 	brick = choose_brick(all, strip->wall);
// 	h_resized_brick = dimension_resized_brick(strip, 'h');
// 	w_resized_brick = dimension_resized_brick(strip, 'w');
// 	if (h_resized_brick == 0)
// 		h_resized_brick = 1;
// 	if (w_resized_brick == 0)
// 		w_resized_brick = 1;
// 	y_in_wall = y_in_window - (int)round(strip->ceil_h);
// 	x_in_resized_brick = strip->index % w_resized_brick;
// 	y_in_resized_brick = y_in_wall % h_resized_brick;
// 	x_in_brick = round(x_in_resized_brick * brick->width / w_resized_brick);
// 	y_in_brick = round(y_in_resized_brick * brick->height / h_resized_brick);
// 	return (get_pixel(brick, x_in_brick, y_in_brick));
// }

int	get_pixel_from_brick(t_all *all, t_strip *strip, int y_in_window)
{
	mlx_image_t	*brick;
	int			x_in_resized_brick;
	int			y_in_resized_brick;
	int			y_in_wall;
	int			x_in_brick;
	int			y_in_brick;
	int			h_resized_brick;
	int			w_resized_brick;

	brick = choose_brick(all, strip->wall);
	h_resized_brick = dimension_resized_brick(strip, 'h');
	w_resized_brick = dimension_resized_brick(strip, 'w');
	if (h_resized_brick == 0)
		h_resized_brick = 1;
	if (w_resized_brick == 0)
		w_resized_brick = 1;
	y_in_wall = y_in_window - (int)round(strip->ceil_h);
	x_in_resized_brick = strip->index % w_resized_brick;
	y_in_resized_brick = y_in_wall % h_resized_brick;
	x_in_brick = round(x_in_resized_brick * brick->width / w_resized_brick);
	y_in_brick = round(y_in_resized_brick * brick->height / h_resized_brick);
	return (get_pixel(brick, x_in_brick, y_in_brick));
}

void	put_pixels_of_strip(t_all *all, t_strip *strip)
{
	int	int_color;
	int	j;

	j = 0;
	while (j < WINDOW_HEIGHT)
	{
		if (j <= (int)floor(strip->ceil_h))
			int_color = all->ceil_color;
		else if (j > (int)floor(strip->ceil_h)
				&& j < ((int)(floor(strip->ceil_h) + floor(strip->wall_h))))
			int_color = get_pixel_from_brick(all, strip, j);
		else
			int_color = all->floor_color;
		if (strip->x >= 0 && strip->x < WINDOW_WIDTH)
			mlx_put_pixel(all->image, strip->x, j, int_color);
		j++;
	}
}

void	strip_to_image(t_all *all)
{
	t_strip	*strip;

	all->image = mlx_new_image(all->window, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!all->image)
		terminate(all, 1);
	strip = all->strip;
	while (strip)
	{
		put_pixels_of_strip(all, strip);
		strip = strip->next;
	}
	mlx_image_to_window(all->window, all->image, 0, 0);
}
