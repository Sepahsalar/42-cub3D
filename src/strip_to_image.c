/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_to_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:13:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/14 17:17:00 by asohrabi         ###   ########.fr       */
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
