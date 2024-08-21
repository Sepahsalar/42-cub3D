/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termiante.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:23:46 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/21 10:40:49 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	free_map_contents(t_map *map)
{
	if (map->north)
		free(map->north);
	if (map->south)
		free(map->south);
	if (map->west)
		free(map->west);
	if (map->east)
		free(map->east);
	if (map->f)
		free(map->f);
	if (map->c)
		free(map->c);
	if (map->start)
		clean_loc(map->start);
	if (map)
		free(map); //update this to free_map
}

void	terminate(t_all *all, int status)
{
	if (all->fd != -1)
		close(all->fd);
	if (all->strip)
		clean_strips(all);
	if (all->map)
		free_map_contents(all->map);
	if (all->strmap)
		free(all->strmap);
	if (status)
		ft_putendl_fd("Error", 2);
	if (all->image)
		mlx_delete_image(all->window, all->image);
	if (all->north)
		mlx_delete_image(all->window, all->north);
	if (all->south)
		mlx_delete_image(all->window, all->south);
	if (all->west)
		mlx_delete_image(all->window, all->west);
	if (all->east)
		mlx_delete_image(all->window, all->east);
	//clean all->minimap
	//clean->all->player_image
	//clean->all->player_image_at_0
	if (all->window)
		mlx_terminate(all->window);
	// if (all->window_name)
	// 	free(all->window_name);
	free(all);
	exit(status);
}

void	check_failure(int input1, void *input2, int type, t_all *all)
{
	if ((input1 < 0 && type == 1) || (type == 2 && input2 == NULL))
		terminate(all, 1);
}
