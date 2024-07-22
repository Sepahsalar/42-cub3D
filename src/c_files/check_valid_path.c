/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:31:54 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/19 16:06:05 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_check_flood_fill(t_map_data	*start)
{
	t_map_data	*node;

	node = start;
	while (node)
	{
		if ((*node).ch == 'E' && !(*node).t)
		{
			ft_free_map_data(start);
			ft_exit_failure(0, 0, "No valid path");
		}
		if ((*node).ch == 'C' && !(*node).t)
		{
			ft_free_map_data(start);
			ft_exit_failure(0, 0, "No valid path");
		}
		node = node->next;
	}
}

void	ft_check_valid_path(char *map)
{
	t_map_data	*start;

	start = ft_create_map_data(map, -1, 0);
	ft_flood(start);
	ft_check_flood_fill(start);
	ft_free_map_data(start);
}
