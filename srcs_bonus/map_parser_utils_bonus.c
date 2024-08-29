/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:26:07 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/29 11:32:13 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static void	update_map(t_all *all, char *found)
{
	char	*start_part1;
	char	*end_part1;
	char	*start_part2;
	char	*temp;
	int		len;

	start_part1 = all->strmap;
	end_part1 = found;
	start_part2 = found;
	while (*start_part2 && *start_part2 != '\n')
		start_part2++;
	len = end_part1 - start_part1;
	temp = malloc(len + ft_strlen(start_part2) + 1);
	if (!temp)
		terminate(all, "Allocating memory failed", NULL, NULL);
	ft_memcpy(temp, all->strmap, len);
	ft_memcpy(temp + len, start_part2, ft_strlen(start_part2) + 1);
	check_empty_map(all, start_part2, "Wrong map structure");
	free(all->strmap);
	all->strmap = temp;
}

static int	custom_strdup_len(char *start)
{
	char	*end;
	int		len;

	end = start;
	while (*end && *end != '\n')
		end++;
	len = end - start;
	return (len);
}

void	check_texture_exists(t_all *all, char *address)
{
	int	fd;

	fd = open(address, O_RDONLY);
	if (fd == -1)
		terminate(all, "Invalid texture path", NULL, NULL);
	if (close(fd) == -1)
		terminate(all, "Closing file failed", NULL, NULL);
}

static void	check_no_information(t_all *all, char *str, char *temp)
{
	if (ft_strlen(temp) == 0)
		terminate(all, "There is no information for ", str,
			" identifier in the map");
}

char	*custom_strdup(t_all *all, char *found, char *str)
{
	char	*start;
	int		len;
	char	*dup;
	char	*temp;

	start = found;
	while (*start != ' ')
		start++;
	len = custom_strdup_len(start);
	dup = malloc(len + 1);
	if (!dup)
		terminate(all, "Allocating memory failed", NULL, NULL);
	ft_memcpy(dup, start, len);
	dup[len] = '\0';
	update_map(all, found);
	temp = ft_strtrim(dup, " ");
	free(dup);
	check_no_information(all, str, temp);
	if (str[0] != 'F' && str[0] != 'C')
		check_texture_exists(all, temp);
	return (temp);
}
