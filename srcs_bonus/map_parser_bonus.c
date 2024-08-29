/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:09:57 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/29 11:32:13 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	remove_white_space(t_all *all)
{
	char	*start;
	char	*temp;

	start = all->strmap;
	temp = all->strmap;
	while (temp && *temp != '1')
	{
		if (*temp == '\n')
			start = temp + 1;
		temp++;
	}
	temp = ft_strdup(start);
	if (!temp)
		terminate(all, "Duplicating string failed", NULL, NULL);
	free(all->strmap);
	all->strmap = temp;
}

static void	check_wrong_identifier(t_all *all)
{
	char	*temp;

	temp = all->strmap;
	while (*temp)
	{
		if (*temp != 'N' && *temp != 'S' && *temp != 'E' && *temp != 'W'
			&& *temp != '1' && *temp != '0' && *temp != ' ' && *temp != '\n')
			terminate(all, "Invalid character",
				" or extra identifier in the map", NULL);
		temp++;
	}
}

void	check_empty_map(t_all *all, char *str, char *error)
{
	char	*temp;

	if (str)
		temp = str;
	else
		temp = all->strmap;
	while (*temp)
	{
		if (*temp != ' ' && *temp != '\n')
			return ;
		temp++;
	}
	terminate(all, error, NULL, NULL);
}

void	find_remove_texture_color(t_all *all)
{
	all->map->north = finder(all, "NO");
	all->map->south = finder(all, "SO");
	all->map->west = finder(all, "WE");
	all->map->east = finder(all, "EA");
	all->map->f = finder(all, "F");
	check_valid_color(all, 'F');
	all->map->c = finder(all, "C");
	check_valid_color(all, 'C');
}

t_map	*map_parser(t_all *all)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (0);
	ft_memset(map, 0, sizeof(t_map));
	all->map = map;
	reader(all);
	check_empty_map(all, NULL, "Empty map");
	find_remove_texture_color(all);
	check_empty_map(all, NULL, "There is no map content in the file");
	check_wrong_identifier(all);
	remove_white_space(all);
	create_loc(all);
	flood_map(all);
	check_dry(all);
	all->map_width = game_size(all, 'x');
	all->map_height = game_size(all, 'y');
	ignore_inside_surface(all);
	return (map);
}
