/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_to_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:13:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/26 15:45:30 by asohrabi         ###   ########.fr       */
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
	size.h_rs_brick = dimension_resized_brick(strip, 'h', brick);
	if (size.h_rs_brick == 0)
		size.h_rs_brick = 1;
	size.w_rs_brick = dimension_resized_brick(strip, 'w', brick);
	if (size.w_rs_brick == 0)
		size.w_rs_brick = 1;
	if (strip->wall == 'N' || strip->wall == 'S')
		size.x_rs_brick = (int)round((double)(strip->x_intersection
					- strip->x_wall) * size.w_rs_brick);
	else
		size.x_rs_brick = (int)round((double)(strip->y_intersection
					- strip->y_wall) * size.w_rs_brick);
	size.y_in_wall = y_in_window - (int)round(strip->ceil_h);
	size.y_rs_brick = size.y_in_wall % size.h_rs_brick;
	size.y_in_brick = round(size.y_rs_brick * brick->height / size.h_rs_brick);
	size.x_in_brick = round(size.x_rs_brick * brick->width / size.w_rs_brick);
	if (size.x_in_brick >= (int)brick->width)
		size.x_in_brick = brick->width - 1;
	if (size.y_in_brick >= (int)brick->height)
		size.y_in_brick = brick->height - 1;
	return (get_pixel(brick, size.x_in_brick, size.y_in_brick));
}

static void	put_pixels_of_strips(t_all *all, t_strip *strip)
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
		terminate(all, "Creating image failed", NULL, NULL);
	strip = all->strip;
	while (strip)
	{
		put_pixels_of_strips(all, strip);
		strip = strip->next;
	}
	mlx_image_to_window(all->window, all->image, 0, 0);
	all->image->instances[0].z = 0;
}
