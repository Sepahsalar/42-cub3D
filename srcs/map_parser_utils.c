/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 14:26:07 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/21 10:40:49 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
	check_failure(0, temp, 2, all);
	ft_memcpy(temp, all->strmap, len);
	ft_memcpy(temp + len, start_part2, ft_strlen(start_part2) + 1);
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
