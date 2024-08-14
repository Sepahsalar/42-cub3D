/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:15:54 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/14 17:17:05 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

int	color(int r, int g, int b, int a)
{
	if (r >= 0 && g >= 0 && b >= 0 && a >= 0 && r <= 255 && g <= 255 && b <= 255
		&& a <= 255)
		return (r << 24 | g << 16 | b << 8 | a);
	if (r < 0)
		return (color(0, g, b, a));
	if (g < 0)
		return (color(r, 0, b, a));
	if (b < 0)
		return (color(r, g, 0, a));
	if (a < 0)
		return (color(r, g, b, 0));
	if (r > 255)
		return (color(255, g, b, a));
	if (g > 255)
		return (color(r, 255, b, a));
	if (b > 255)
		return (color(r, g, 255, a));
	return (color(r, g, b, 255));
}

int	color_maker(t_all *all, char type)
{
	char	*full_color;
	char	**split;
	int		int_color;

	if (type == 'f')
		full_color = all->map->f;
	else
		full_color = all->map->c;
	if (!full_color)
		terminate(all, 1);
	split = ft_split(full_color, ',');
	if (!split)
		terminate(all, 1);
	if (!split[3])
		int_color = color(ft_atoi(split[0]), ft_atoi(split[1]),
				ft_atoi(split[2]), 255);
	else
		int_color = color(ft_atoi(split[0]), ft_atoi(split[1]),
				ft_atoi(split[2]), ft_atoi(split[3]));
	clean_2d_char_array(split);
	return (int_color);
}
