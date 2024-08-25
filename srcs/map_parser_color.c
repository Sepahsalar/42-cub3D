/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nima <nnourine@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:42:31 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/25 15:41:35 by nima             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

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
				ft_putstr_fd(" identifier contains characters", 2);
				ft_putendl_fd(" which are not digits", 2);
				terminate(all, 1);
			}
			j++;
		}
		i++;
	}
}

static void	check_rgb_format(t_all *all, char **split, char type)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		clean_2d_char_array(split);
		ft_putstr_fd("The color for ", 2);
		ft_putchar_fd(type, 2);
		ft_putendl_fd(" identifier does not match the RGB model", 2);
		terminate(all, 1);
	}
}

void	check_valid_range_foramat(t_all *all, char **split,
	char *trimmed, char type)
{
	if (trimmed[0] == '0' && ft_strlen(trimmed) > 1)
	{
		free(trimmed);
		clean_2d_char_array(split);
		ft_putstr_fd("Invalid number format for ", 2);
		ft_putchar_fd(type, 2);
		ft_putendl_fd(" identifier in the map", 2);
		terminate(all, 1);
	}
	if (ft_strlen(trimmed) > 3 || ft_atoi(trimmed) < 0
		|| ft_atoi(trimmed) > 255)
	{
		free(trimmed);
		clean_2d_char_array(split);
		ft_putstr_fd("Invalid color range for ", 2);
		ft_putchar_fd(type, 2);
		ft_putendl_fd(" identifier in the map", 2);
		terminate(all, 1);
	}
}

static void	valid_range(t_all *all, char **split, char type)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (split[i])
	{
		trimmed = ft_strtrim(split[i], " ");
		if (!trimmed)
			terminate(all, 1);
		check_valid_range_foramat(all, split, trimmed, type);
		free(trimmed);
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
	if (full_color[ft_strlen(full_color) - 1] == ',')
	{
		ft_putstr_fd("The color for ", 2);
		ft_putchar_fd(type, 2);
		ft_putendl_fd(" identifier does not match the RGB model", 2);
		terminate(all, 1);
	}
	split = ft_split(full_color, ',');
	if (!split)
		terminate(all, 1);
	check_rgb_format(all, split, type);
	only_digit(all, split, type);
	valid_range(all, split, type);
	clean_2d_char_array(split);
}
