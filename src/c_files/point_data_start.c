/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_data_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 11:57:39 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/19 16:06:05 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

t_point_data	ft_point_data_start(char *map, t_elements_count elements_count)
{
	t_point_data	point_data;

	point_data.fd_map = open(map, O_RDONLY);
	point_data.x_position = 0;
	point_data.y_position = 0;
	point_data.character = '\0';
	point_data.character_width
		= elements_count.image_width;
	point_data.character_height
		= elements_count.image_height;
	return (point_data);
}
