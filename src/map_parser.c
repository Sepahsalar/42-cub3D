/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:09:57 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/14 10:25:48 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	update_map(t_all *all, char *found)
{
	char	*end_part1;
	char	*start_part2;
	char	*temp;
	int		len1;
	int		len2;

	end_part1 = all->strmap;
	temp = all->strmap;
	while(temp < found)
	{
		if (*temp == '\n')
			end_part1 = temp;
		temp++;
	}
	while (*found != '\n')
		found++;
	start_part2 = found + 1;
	len1 = end_part1 - all->strmap;
	len2 = ft_strlen(start_part2);
	temp = malloc(len1 + len2 + 1);
	check_failure(0, temp, 2, all);
	ft_memcpy(temp, all->strmap, len1);
	ft_memcpy(temp + len1, start_part2, len2 + 1);
	free(all->strmap);
	all->strmap = temp;
}

char	*custom_strdup(t_all *all, char *found, char *str)
{
	char	*start;
	char	*end;
	int		len;
	char	*dup;

	start = found;
	while (*start != ' ')
		start++;
	while (*start == ' ')
		start++;
	end = start;
	while (end && *end != ' ' && *end != '\n')
		end++;
	len = end - start;
	if (len == 0)
	{
		ft_putstr_fd("There is no information for ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" identifier in the map", 2);
		terminate(all, 1);
	}
	dup = malloc(len + 1);
	check_failure(0, dup, 2, all);
	ft_memcpy(dup, start, len);
	dup[len] = '\0';
	update_map(all, found);
	return (dup);    
}

char	*finder(t_all *all, char *str)
{
    char *found;
    
	found = ft_strnstr(all->strmap, str, ft_strlen(all->strmap));
    if (found)
		return(custom_strdup(all, found, str));
	ft_putstr_fd("There is no ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(" identifier in the map", 2);
	terminate(all, 1);
	return (NULL);
}

void	remove_white_space(t_all *all)
{
	char *start;
	char *temp;
	
	start = all->strmap;
	temp = all->strmap;
	while (temp && *temp != '1')
	{
		if (*temp == '\n')
			start = temp + 1;
		temp++;
	}
	// free(all->strmap);
	temp = ft_strdup(start);
	check_failure(0, temp, 2, all);
	free(all->strmap);
	all->strmap = temp;
}

t_map	*map_parser(t_all *all)
{
    t_map   *map;

    map = malloc(sizeof(t_map));
    if (!map)
		return (0);
	all->map = map;
	reader(all);
	all->map->north = finder(all, "NO");
	all->map->south = finder(all, "SO");
	all->map->west = finder(all, "WE");
	all->map->east = finder(all, "EA");
	all->map->f = finder(all, "F");
	all->map->c = finder(all, "C");
	remove_white_space(all);
	create_loc(all);
	all->map_width = game_size(all, 'x');
	all->map_height = game_size(all, 'y');
	ignore_inside_surface(all);
	return (map); 
}
