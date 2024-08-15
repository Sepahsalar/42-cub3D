/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 19:25:50 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/15 20:01:16 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void create_minimap(t_all *all)
{
	t_loc *loc;
	int int_color_wall;
	int int_color_floor;
	int int_color_player;
	int i;
	int j;

	loc = all->map->start;
	all->minimap = mlx_new_image(all->window, (all->map_width) * 15, (all->map_height) * 15);
	all->wall_small = mlx_new_image(all->window, 15, 15);
	int_color_wall = color(0, 0, 0, 255);
	int_color_floor = color(255, 255, 255, 150);
	i = 0;
	while(i < (int)all->minimap->width)
	{
		j = 0;
		while(j < (int)all->minimap->height)
		{
			mlx_put_pixel(all->minimap, i, j, int_color_floor);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < (int)all->wall_small->width)
	{
		j = 0;
		while (j < (int)all->wall_small->height)
		{
			mlx_put_pixel(all->wall_small, i, j, int_color_wall);
			j++;
		}
		i++;
	}
	mlx_image_to_window(all->window, all->minimap, 50, 50);
	while (loc)
	{
		if (loc->c == '1')
			mlx_image_to_window(all->window, all->wall_small, (loc->x * 15) + 50, (loc->y * 15) + 50);
		loc = loc->next;
	}
	all->player = mlx_new_image(all->window, 15, 15);
	int_color_player = color(255, 0, 0, 255);
	i = 0;
	while (i < (int)all->player->width)
	{
		j = 0;
		while (j < (int)all->player->height)
		{
			mlx_put_pixel(all->player, i, j, int_color_player);
			j++;
		}
		i++;
	}
	mlx_image_to_window(all->window, all->player, ((all->x - 0.5)  * 15) + 50, ((all->y - 0.5) * 15) + 50);
	
	
	
	
	
	
}