/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:23:46 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/29 14:56:37 by asohrabi         ###   ########.fr       */
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

void	print_error(char *str1, char *str2, char *str3)
{
	if (str1)
	{
		ft_putendl_fd("Error", 2);
		ft_putstr_fd(str1, 2);
		if (str2)
		{
			ft_putstr_fd(str2, 2);
			if (str3)
				ft_putendl_fd(str3, 2);
			else
				ft_putchar_fd('\n', 2);
		}
		else
			ft_putchar_fd('\n', 2);
		exit(1);
	}
}

void	terminate(t_all *all, char *str1, char *str2, char *str3)
{
	if (all->strip)
		clean_strips(all);
	if (all->map)
		free_map_contents(all->map);
	if (all->strmap)
		free(all->strmap);
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
	if (all->window)
		mlx_terminate(all->window);
	free(all);
	print_error(str1, str2, str3);
	exit(0);
}
