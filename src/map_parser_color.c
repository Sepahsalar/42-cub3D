/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:42:31 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/14 18:37:28 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static void	only_digit(t_all *all, char **split, char type)
{
	int	i;
	int	j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (!ft_isdigit(split[i][j]) && split[i][j] != ' ')
			{
				clean_2d_char_array(split);
				ft_putchar_fd(type, 2);
				ft_putendl_fd(" identifier contains characters", 2);
				ft_putendl_fd(" which are not digits", 2);
				terminate(all, 1);
			}
			j++;
		}
		i++;
	}
}

static void	only_three_or_four_parts(t_all *all, char **split, char type)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i != 3 && i != 4)
	{
		clean_2d_char_array(split);
		ft_putstr_fd("Wrong number of color parts for ", 2);
		ft_putchar_fd(type, 2);
		ft_putendl_fd(" identifier in the map", 2);
		terminate(all, 1);
	}
}

static void	valid_range(t_all *all, char **split, char type)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (ft_atoi(split[i]) < 0 || ft_atoi(split[i]) > 255)
		{
			clean_2d_char_array(split);
			ft_putstr_fd("Invalid color range for ", 2);
			ft_putchar_fd(type, 2);
			ft_putendl_fd(" identifier in the map", 2);
			terminate(all, 1);
		}
		i++;
	}
}

void	check_valid_color(t_all *all, char type)
{
	char	*full_color;
	char	**split;

	if (type == 'F')
		full_color = all->map->f;
	else
		full_color = all->map->c;
	if (!full_color)
		terminate(all, 1);
	split = ft_split(full_color, ',');
	if (!split)
		terminate(all, 1);
	only_three_or_four_parts(all, split, type);
	only_digit(all, split, type);
	valid_range(all, split, type);
	clean_2d_char_array(split);
}
