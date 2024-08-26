/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 19:25:50 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/26 16:12:06 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	is_there_a_wall(t_all *all, int x, int y)
{
	int		x_minimap_to_loc;
	int		y_minimap_to_loc;
	t_loc	*loc;

	x_minimap_to_loc = all->x - 0.5 - MINIMAP_COVERAGE / 2
		+ (x + (MINIMAP_SIDE / (2 * MINIMAP_COVERAGE)))
		/ (MINIMAP_SIDE / MINIMAP_COVERAGE);
	y_minimap_to_loc = all->y - 0.5 - MINIMAP_COVERAGE / 2
		+ (y + (MINIMAP_SIDE / (2 * MINIMAP_COVERAGE)))
		/ (MINIMAP_SIDE / MINIMAP_COVERAGE);
	loc = all->map->start;
	while (loc)
	{
		if (loc->x == x_minimap_to_loc && loc->y == y_minimap_to_loc)
			return (1);
		loc = loc->next;
	}
	return (0);
}

void	create_minimap(t_all *all)
{
	int	int_color_wall;
	int	int_color_floor;
	int	i;
	int	j;

	all->minimap = mlx_new_image(all->window, MINIMAP_SIDE, MINIMAP_SIDE);
	int_color_wall = color(0, 0, 0, 255);
	int_color_floor = color(255, 255, 255, 150);
	i = 0;
	while (i < (int)all->minimap->width)
	{
		j = 0;
		while (j < (int)all->minimap->height)
		{
			if (is_there_a_wall(all, i, j))
				mlx_put_pixel(all->minimap, i, j, int_color_wall);
			else
				mlx_put_pixel(all->minimap, i, j, int_color_floor);
			j++;
		}
		i++;
	}
	mlx_image_to_window(all->window, all->minimap,
		MINIMAP_PADDING, MINIMAP_PADDING);
	all->minimap->instances[0].z = 1;
}
