/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:42:31 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/26 17:44:00 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	only_digit(t_all *all, char **split, char type)
{
	int		i;
	int		j;
	char	str[2];

	i = 0;
	str[1] = '\0';
	str[0] = type;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (!ft_isdigit(split[i][j]) && split[i][j] != ' ')
			{
				clean_2d_char_array(split);
				terminate(all, str, " identifier contains characters",
					" which are not digits");
			}
			j++;
		}
		i++;
	}
}

static void	check_rgb_format(t_all *all, char **split, char type)
{
	int		i;
	char	str[2];

	i = 0;
	str[1] = '\0';
	str[0] = type;
	while (split[i])
		i++;
	if (i != 3)
	{
		clean_2d_char_array(split);
		terminate(all, "The color for ", str,
			" identifier does not match the RGB model");
	}
}

void	check_valid_range_foramat(t_all *all, char **split, char *trimmed,
		char type)
{
	char	str[2];

	str[1] = '\0';
	str[0] = type;
	if (trimmed[0] == '0' && ft_strlen(trimmed) > 1)
	{
		free(trimmed);
		clean_2d_char_array(split);
		terminate(all, "Invalid number format for ", str,
			" identifier in the map");
	}
	if (ft_strlen(trimmed) > 3 || ft_atoi(trimmed) < 0
		|| ft_atoi(trimmed) > 255)
	{
		free(trimmed);
		clean_2d_char_array(split);
		terminate(all, "Invalid color range for ", str,
			" identifier in the map");
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
			terminate(all, "Trimming string failed", NULL, NULL);
		check_valid_range_foramat(all, split, trimmed, type);
		free(trimmed);
		i++;
	}
}

void	check_valid_color(t_all *all, char type)
{
	char	*full_color;
	char	**split;
	char	str[2];

	if (type == 'F')
		full_color = all->map->f;
	else
		full_color = all->map->c;
	str[1] = '\0';
	str[0] = type;
	if (!full_color)
		terminate(all, "There is no information for ", str,
			" identifier in the map");
	if (full_color[ft_strlen(full_color) - 1] == ',')
		terminate(all, "The color for ", str,
			" identifier does not match the RGB model");
	split = ft_split(full_color, ',');
	if (!split)
		terminate(all, "Splitting string failed", NULL, NULL);
	check_rgb_format(all, split, type);
	only_digit(all, split, type);
	valid_range(all, split, type);
	clean_2d_char_array(split);
}
