/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:09:57 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/22 09:39:39 by nnourine         ###   ########.fr       */
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

char	*custom_strnstr(char *haystack, char *needle)
{
	char	*temp;

	temp = ft_strnstr(haystack, needle, ft_strlen(haystack));
	while (temp)
	{
		if (temp[ft_strlen(needle)] == ' ')
			return (temp);
		temp = ft_strnstr(temp + 1, needle, ft_strlen(haystack));
	}
	return (NULL);
}

char	*finder(t_all *all, char *str)
{
	char	*found;

	found = custom_strnstr(all->strmap, str);
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
	ft_putendl_fd(error, 2);
	terminate(all, 1);
}

void	wet_loc(t_all *all, t_loc *loc)
{
	int		x;
	int		y;
	t_loc	*temp;

	x = loc->x;
	y = loc->y;
	temp = all->map->start;
	while (temp)
	{
		if ((temp->x == x && temp->y == y + 1) || (temp->x == x && temp->y == y
				- 1) || (temp->x == x + 1 && temp->y == y) || (temp->x == x - 1
				&& temp->y == y))
			temp->wet = 1;
		temp = temp->next;
	}
}

int	sum_wet(t_all *all)
{
	t_loc	*loc;
	int		sum;

	loc = all->map->start;
	sum = 0;
	while (loc)
	{
		if (loc->wet == 1)
			sum++;
		loc = loc->next;
	}
	return (sum);
}

void	check_dry(t_all *all)
{
	t_loc	*loc;

	loc = all->map->start;
	while (loc)
	{
		if (loc->wet == 0 && loc->c != '1')
		{
			ft_putendl_fd("Map is separated", 2);
			terminate(all, 1);
		}
		loc = loc->next;
	}
}

void	flood_map(t_all *all)
{
	t_loc	*loc;
	int		sum1;
	int		sum2;

	all->map->start->wet = 1;
	wet_loc(all, all->map->start);
	sum1 = 0;
	sum2 = sum_wet(all);
	while (sum1 < sum2)
	{
		loc = all->map->start;
		while (loc)
		{
			if (loc->wet == 1)
				wet_loc(all, loc);
			loc = loc->next;
		}
		loc = all->map->start;
		sum1 = sum2;
		sum2 = sum_wet(all);
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
	check_empty_map(all, NULL, "Empty map");
	all->map->north = finder(all, "NO");
	all->map->south = finder(all, "SO");
	all->map->west = finder(all, "WE");
	all->map->east = finder(all, "EA");
	all->map->f = finder(all, "F");
	check_valid_color(all, 'F');
	all->map->c = finder(all, "C");
	check_valid_color(all, 'C');
	check_empty_map(all, NULL, "There is no map content in the file");
	check_wrong_identifier(all);
	remove_white_space(all);
	create_loc(all);
	flood_map(all);
	// check_dry(all);
	all->map_width = game_size(all, 'x');
	all->map_height = game_size(all, 'y');
	ignore_inside_surface(all);
	return (map);
}
