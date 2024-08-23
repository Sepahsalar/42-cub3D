/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termiante.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:23:46 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/23 11:57:12 by asohrabi         ###   ########.fr       */
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
		free(map);
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
	if (all->minimap)
		mlx_delete_image(all->window, all->minimap);
	if (all->gun)
		mlx_delete_image(all->window, all->gun);
	if (all->blast)
		mlx_delete_image(all->window, all->blast);
	if (all->player_image)
		clean_player_image(all);
	if (all->player_at_0)
		mlx_delete_image(all->window, all->player_at_0);
	if (all->window)
		mlx_terminate(all->window);
	free(all);
	exit(status);
}

void	check_failure(int input1, void *input2, int type, t_all *all)
{
	if ((input1 < 0 && type == 1) || (type == 2 && input2 == NULL))
		terminate(all, 1);
}
