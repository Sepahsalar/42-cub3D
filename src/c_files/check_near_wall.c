/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_near_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:04:23 by nnourine          #+#    #+#             */
/*   Updated: 2024/03/05 14:55:37 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

int	ft_check_near_wall(t_window_elements *window_elements, char move)
{
	mlx_image_t	*player;
	mlx_image_t	*wall;
	int			count;
	int			index;

	player = (window_elements->elements)->player;
	wall = (window_elements->elements)->wall;
	count = wall->count;
	index = 0;
	while (index < count)
	{
		index = ft_check_with_wall_instance(player, wall, index, move);
		if (!index)
			return (0);
	}
	return (1);
}
