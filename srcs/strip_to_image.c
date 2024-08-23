/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_to_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:13:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/23 16:55:29 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static mlx_image_t	*choose_brick(t_all *all, char wall)
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

static int	dimension_resized_brick(t_strip *strip, char type,
		mlx_image_t *brick)
{
	if (type == 'h')
		return (round(strip->wall_h));
	else
		return (round((brick->width * strip->wall_h) / brick->height));
}

static int	get_pixel_from_brick(t_all *all, t_strip *strip, int y_in_window)
{
	mlx_image_t		*brick;
	t_pixel_bricks	size;

	brick = choose_brick(all, strip->wall);
	size.h_resized_brick = dimension_resized_brick(strip, 'h', brick);
	if (size.h_resized_brick == 0)
		size.h_resized_brick = 1;
	size.w_resized_brick = dimension_resized_brick(strip, 'w', brick);
	if (size.w_resized_brick == 0)
		size.w_resized_brick = 1;
	if (strip->wall == 'N' || strip->wall == 'S')
		size.x_in_resized_brick = (int)round((double)(strip->x_intersection
					- strip->x_wall) * size.w_resized_brick);
	else
		size.x_in_resized_brick = (int)round((double)(strip->y_intersection
					- strip->y_wall) * size.w_resized_brick);
	// if (strip->ceil_h >= 0)
	size.y_in_wall = y_in_window - (int)round(strip->ceil_h);
	// else
	// 	size.y_in_wall = y_in_window;
	size.y_in_resized_brick = size.y_in_wall % size.h_resized_brick;
	size.y_in_brick = round(size.y_in_resized_brick * brick->height
			/ size.h_resized_brick);
	size.x_in_brick = round(size.x_in_resized_brick * brick->width
			/ size.w_resized_brick);
	return (get_pixel(brick, size.x_in_brick, size.y_in_brick));
}

static void	put_pixels_of_strips(t_all *all, t_strip *strip)
{
	int	int_color;
	int	j;
	// double temp;

	j = 0;
	if (strip->wall_h < WINDOW_HEIGHT)
	{
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
	else
	{
		while (j < WINDOW_HEIGHT)
		{
			// temp = strip->wall_h;
			// strip->wall_h = WINDOW_HEIGHT;
			int_color = get_pixel_from_brick(all, strip, j);
			// - (strip->wall_h - WINDOW_HEIGHT));
			if (strip->x >= 0 && strip->x < WINDOW_WIDTH)
				mlx_put_pixel(all->image, strip->x, j, int_color);
			j++;
		}
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
		put_pixels_of_strips(all, strip);
		strip = strip->next;
	}
	mlx_image_to_window(all->window, all->image, 0, 0);
	all->image->instances[0].z = 0;
}
