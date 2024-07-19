/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:23:57 by nnourine          #+#    #+#             */
/*   Updated: 2024/03/05 15:57:05 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

t_collectible_position	*ft_create_collectible_node(t_point_data point_data)
{
	t_collectible_position	*new;

	new = malloc(sizeof(t_collectible_position));
	if (!new)
		return (0);
	(*new).x = point_data.x_position;
	(*new).y = point_data.y_position;
	(*new).enabled = 1;
	new->next = 0;
	return (new);
}

void	ft_positon_update(t_point_data *point_data)
{
	if ((*point_data).character == '\n')
	{
		(*point_data).x_position = 0;
		(*point_data).y_position++;
	}
	else
		(*point_data).x_position++;
}

t_collectible_position	*ft_malloc_fail(t_point_data point_data,
	t_collectible_position *first_collectible)
{
	close(point_data.fd_map);
	ft_free_collectible_list(first_collectible);
	return (0);
}

t_collectible_position	*ft_create_collectible_list(
		t_elements_count elements_count,
		t_collectible_position *first_collectible)
{
	t_collectible_position	*new_collectible;
	t_collectible_position	*old_collectible;
	t_point_data			point_data;

	point_data = ft_point_data_start(elements_count.map, elements_count);
	if (point_data.fd_map == -1)
		return (0);
	while (read(point_data.fd_map, &(point_data.character), 1))
	{
		if (point_data.character == 'C')
		{
			new_collectible = ft_create_collectible_node(point_data);
			if (!new_collectible)
				return (ft_malloc_fail(point_data, first_collectible));
			if (!first_collectible)
				first_collectible = new_collectible;
			else
				old_collectible->next = new_collectible;
			old_collectible = new_collectible;
		}
		ft_positon_update(&point_data);
	}
	close(point_data.fd_map);
	return (first_collectible);
}

t_player_collectible	*ft_start_position(mlx_t *window,
	t_elements_count elements_count)
{
	t_player_collectible	*player_collectible;
	t_collectible_position	*collectible;

	player_collectible = malloc(sizeof(t_player_collectible));
	if (!player_collectible)
		ft_exit_failure(window, 0,
			"Playe_collectible memory allocation problem");
	(*player_collectible).player_position
		= ft_player_position(elements_count.map);
	collectible = 0;
	collectible = ft_create_collectible_list(elements_count, 0);
	if (!collectible)
	{
		free(player_collectible);
		ft_exit_failure(window, 0, "Collectible creating list problem");
	}
	player_collectible->collectible = collectible;
	return (player_collectible);
}
