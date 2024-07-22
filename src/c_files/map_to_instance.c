/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_instance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:03:40 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/19 16:06:05 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_map_to_instance_background(mlx_t *window, t_elements *elements)
{
	mlx_image_t	*background;

	background = elements->empty_space;
	if (mlx_image_to_window(window, background, 0, 0) == -1)
		ft_exit_failure(window, elements, "backgroubd instance making problem");
}

void	ft_create_instance(mlx_t *window,
	t_elements *elements, t_point_data point_data)
{
	mlx_image_t	*image;

	if (point_data.character == '0')
		return ;
	if (point_data.character == '1')
		image = elements->wall;
	else if (point_data.character == 'C')
		image = elements->collectible;
	else if (point_data.character == 'E')
		image = elements->exit;
	else
		image = elements->player;
	if (mlx_image_to_window(window, image,
			point_data.x_position, point_data.y_position) == -1)
		ft_exit_failure(window, elements, "Instance making problem");
}

void	ft_map_to_instance_except_player(mlx_t *window,
	t_elements *elements, t_elements_count elements_count, char *map)
{
	t_point_data	point_data;

	point_data = ft_point_data_start(map, elements_count);
	if (point_data.fd_map == -1)
		ft_exit_failure(window, elements, "Map opening problem");
	while (read(point_data.fd_map, &(point_data.character), 1))
	{
		if (point_data.character == '\n')
		{
			point_data.x_position = 0;
			point_data.y_position
				= point_data.y_position + point_data.character_height;
		}
		else
		{
			if (point_data.character != 'P' && point_data.character != '0')
				ft_create_instance(window, elements, point_data);
			point_data.x_position
				= point_data.x_position + point_data.character_width;
		}
	}
	close(point_data.fd_map);
}

void	ft_map_to_instance_player(mlx_t *window,
	t_elements *elements, t_elements_count elements_count, char *map)
{
	t_point_data	point_data;

	point_data = ft_point_data_start(map, elements_count);
	if (point_data.fd_map == -1)
		ft_exit_failure(window, elements, "Map opening problem");
	while (read(point_data.fd_map, &(point_data.character), 1))
	{
		if (point_data.character == '\n')
		{
			point_data.x_position = 0;
			point_data.y_position
				= point_data.y_position + point_data.character_height;
		}
		else
		{
			if (point_data.character == 'P')
				ft_create_instance(window, elements, point_data);
			point_data.x_position
				= point_data.x_position + point_data.character_width;
		}
	}
	close(point_data.fd_map);
}

void	ft_map_to_instance(mlx_t *window, t_elements *elements,
	t_elements_count elements_count, char *map)
{
	ft_map_to_instance_background(window, elements);
	ft_map_to_instance_except_player(window, elements, elements_count, map);
	ft_map_to_instance_player(window, elements, elements_count, map);
}
