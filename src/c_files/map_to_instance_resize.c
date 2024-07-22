/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_instance_resize.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:56:54 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/19 16:06:05 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_create_instance_resize(mlx_t *window,
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

void	ft_map_to_instance_except_wall_exit_resize(mlx_t *window,
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
		else if (point_data.character == '1' || point_data.character == 'E')
		{
			ft_create_instance(window, elements, point_data);
			point_data.x_position
				= point_data.x_position + point_data.character_width;
		}
		else
			point_data.x_position = point_data.x_position
				+ point_data.character_width;
	}
	close(point_data.fd_map);
}

void	ft_map_to_instance_collectible_resize(mlx_t *window,
	t_elements *elements)
{
	t_collectible_position	*collectible_list;
	t_collectible_position	*node;
	mlx_image_t				*image;

	image = elements->collectible;
	collectible_list = (elements->player_collectible)->collectible;
	node = collectible_list;
	while (node)
	{
		if ((*node).enabled)
		{
			if (mlx_image_to_window(window, image, ((*node).x * image->width),
					((*node).y * image->height)) == -1)
				ft_exit_failure(window, elements, "Instance making problem");
		}
		node = node->next;
	}
}

void	ft_map_to_instance_player_resize(mlx_t *window,
	t_elements *elements)
{
	int	player_position_x;
	int	player_position_y;

	player_position_x = (*(elements->player_collectible)).player_position.x;
	player_position_y = (*(elements->player_collectible)).player_position.y;
	if (mlx_image_to_window(window, elements->player,
			player_position_x * (elements->player)->width,
			player_position_y * (elements->player)->height) == -1)
		ft_exit_failure(window, elements, "Instance making problem");
}

void	ft_map_to_instance_resize(mlx_t *window,
	t_elements *elements,
	t_elements_count elements_count, char *map)
{
	ft_map_to_instance_background_resize(window, elements);
	ft_map_to_instance_except_wall_exit_resize(window, elements,
		elements_count, map);
	ft_map_to_instance_collectible_resize(window, elements);
	ft_map_to_instance_player_resize(window, elements);
}
