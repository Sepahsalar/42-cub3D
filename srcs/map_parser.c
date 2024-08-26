/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:09:57 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/26 12:46:52 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void check_open_failure(t_all *all, int fd)
{
	if (fd == -1)
		terminate(all, "Opening map file failed", NULL, NULL);
}

void	reader(t_all *all)
{
	char	c[2];
	int		byte;
	char	*temp;
	int		fd;

	c[1] = '\0';
	all->strmap = NULL;
	fd = open(all->argv, O_RDONLY);
	check_open_failure(all, fd);
	byte = read(fd, c, 1);
	if (byte == -1)
		terminate(all, "Reading from file failed", NULL, NULL);
	while (byte)
	{
		temp = all->strmap;
		all->strmap = ft_strjoin(all->strmap, c);
		free(temp);
		if (!all->strmap)
			terminate(all, "Joining strings failed", NULL, NULL);
		byte = read(fd, c, 1);
		if (byte == -1)
			terminate(all, "Reading from file failed", NULL, NULL);
	}
	if (close(fd) == -1)
		terminate(all, "Closing file failed", NULL, NULL);
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
	terminate(all, "There is no ", str, " identifier in the map");
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
			terminate(all, "Invalid character", " or extra identifier in the map", NULL);
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
		if (loc->wet == 0)
			terminate(all, "Map is separated", NULL, NULL);
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

void find_remove_texture_color(t_all *all)
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
