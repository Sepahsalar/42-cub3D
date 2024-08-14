/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:26:07 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/14 17:46:05 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	update_map(t_all *all, char *found)
{
	char	*start_part1;
	char	*end_part1;
	char	*start_part2;
	char	*temp;
	int		len1;
	int		len2;

	start_part1 = all->strmap;
	end_part1 = found;
	start_part2 = found;
	while (*start_part2 && *start_part2 != '\n')
		start_part2++;
	len1 = end_part1 - start_part1;
	len2 = ft_strlen(start_part2);
	temp = malloc(len1 + len2 + 1);
	check_failure(0, temp, 2, all);
	ft_memcpy(temp, all->strmap, len1);
	ft_memcpy(temp + len1, start_part2, len2 + 1);
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
	check_failure(0, dup, 2, all);
	ft_memcpy(dup, start, len);
	dup[len] = '\0';
	update_map(all, found);
	temp = ft_strtrim(dup, " ");
	free(dup);
	if (ft_strlen(temp) == 0)
	{
		ft_putstr_fd("There is no information for ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" identifier in the map", 2);
		terminate(all, 1);
	}
	return (temp);
}

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
	// free(all->strmap);
	temp = ft_strdup(start);
	check_failure(0, temp, 2, all);
	free(all->strmap);
	all->strmap = temp;
}
