/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:01:24 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/29 12:27:43 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	clean_2d_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	check_map_format(char *str)
{
	if (ft_strlen(str) < 5)
		return (0);
	if (str[ft_strlen(str) - 5] == '/')
		return (0);
	if (str[ft_strlen(str) - 4] != '.' || str[ft_strlen(str) - 3] != 'c'
		|| str[ft_strlen(str) - 2] != 'u' || str[ft_strlen(str) - 1] != 'b')
		return (0);
	return (1);
}

int	game_size(t_all *all, char c)
{
	t_loc	*loc;
	int		i;

	loc = all->map->start;
	i = 0;
	while (loc)
	{
		if (c == 'x')
		{
			if (i < loc->x)
				i = loc->x;
		}
		else
		{
			if (i < loc->y)
				i = loc->y;
		}
		loc = loc->next;
	}
	return (i + 1);
}

double	height(double distance, char c)
{
	double	half_full_height;
	double	target_height;

	half_full_height = ft_tan(VAOV / 2) * distance;
	if (c == 'F')
		target_height = half_full_height - PERSON;
	else
		target_height = half_full_height - WALL + PERSON;
	return ((WINDOW_HEIGHT * target_height / (2 * half_full_height)));
}

int	same(double d1, double d2)
{
	if (fabs(d1 - d2) < EPSILON)
		return (1);
	return (0);
}
