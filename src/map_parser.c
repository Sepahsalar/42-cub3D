/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:09:57 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/07 11:28:15 by asohrabi         ###   ########.fr       */
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
	// // ////printf("end_part1: %s\n", end_part1);
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

char	*custom_strdup(t_all *all, char *found)
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
	dup = malloc(len + 1);
	check_failure(0, dup, 2, all);
	ft_memcpy(dup, start, len);
	dup[len] = '\0';
	// // ////printf("map before update*************\n%s\n", all->strmap);
	// // ////printf("found before update*************\n%s\n", found);
	update_map(all, found);
	// // ////printf("map after update*************\n%s\n", all->strmap);
	return (dup);    
}

char	*finder(t_all *all, char *str)
{
    char *found;
    
	found = ft_strnstr(all->strmap, str, ft_strlen(all->strmap));
	// // ////printf("for str: %s\nfound*************\n%s\n", str, found);
    if (found)
		return(custom_strdup(all, found));
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
	// ////printf("North: %s\n", all->map->north);
	all->map->south = finder(all, "SO");
	// ////printf("South: %s\n", all->map->south);
	all->map->west = finder(all, "WE");
	// ////printf("West: %s\n", all->map->west);
	all->map->east = finder(all, "EA");
	// ////printf("East: %s\n", all->map->east);
	all->map->f = finder(all, "F");
	// ////printf("Floor: %s\n", all->map->f);
	all->map->c = finder(all, "C");
	// ////printf("Ceil: %s\n", all->map->c);
	remove_white_space(all);
	// ////printf("%s\n", all->strmap);
	create_loc(all);
	return (map); 
}
