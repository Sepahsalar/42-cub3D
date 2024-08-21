/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:09:57 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/21 10:40:49 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	reader(t_all *all)
{
	char	c[2];
	int		byte;
	char	*temp;

	c[1] = '\0';
	all->strmap = NULL;
	all->fd = open(all->argv, O_RDONLY);
	if (all->fd == -1)
	{
		ft_putendl_fd("Could not open the map file", 2);
		terminate(all, 1);
	}
	// check_failure(all->fd, NULL, 1, all);
	byte = read(all->fd, c, 1);
	check_failure(byte, NULL, 1, all);
	while (byte)
	{
		temp = all->strmap;
		all->strmap = ft_strjoin(all->strmap, c);
		free(temp);
		check_failure(0, all->strmap, 2, all);
		byte = read(all->fd, c, 1);
		check_failure(byte, NULL, 1, all);
	}
}

char	*finder(t_all *all, char *str)
{
	char	*found;

	found = ft_strnstr(all->strmap, str, ft_strlen(all->strmap));
	if (found)
		return (custom_strdup(all, found, str));
	ft_putstr_fd("There is no ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" identifier in the map", 2);
	terminate(all, 1);
	return (NULL);
}

static void	check_wrong_identifier(t_all *all)
{
	char	*temp;

	temp = all->strmap;
	while (*temp)
	{
		if (*temp != 'N' && *temp != 'S' && *temp != 'E' && *temp != 'W'
			&& *temp != '1' && *temp != '0' && *temp != ' ' && *temp != '\n')
		{
			ft_putstr_fd("Invalid character", 2);
			ft_putendl_fd(" or extra identifier in the map", 2);
			terminate(all, 1);
		}
		temp++;
	}
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
	all->map->north = finder(all, "NO");
	all->map->south = finder(all, "SO");
	all->map->west = finder(all, "WE");
	all->map->east = finder(all, "EA");
	all->map->f = finder(all, "F");
	check_valid_color(all, 'F');
	all->map->c = finder(all, "C");
	check_valid_color(all, 'C');
	check_wrong_identifier(all);
	remove_white_space(all);
	create_loc(all);
	all->map_width = game_size(all, 'x');
	all->map_height = game_size(all, 'y');
	ignore_inside_surface(all);
	return (map);
}
