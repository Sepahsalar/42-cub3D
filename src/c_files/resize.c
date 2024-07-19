/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:14:56 by nnourine          #+#    #+#             */
/*   Updated: 2024/03/08 11:08:56 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/so_long.h"

void	ft_resize(int new_width, int new_height, void *param)
{
	mlx_t				*window;
	t_elements			*elements;
	t_elements_count	elements_count;

	window = ((t_window_elements *) param)->window;
	elements = ((t_window_elements *) param)->elements;
	elements_count = (((t_window_elements *) param))->elements_count;
	(elements_count).image_width = floor(new_width
			/ (elements_count).width_count);
	(elements_count).image_height = floor(new_height
			/ (elements_count).hight_count);
	if ((elements_count).image_width >= MIN_IMAGE_SIZE
		&& (elements_count).image_height >= MIN_IMAGE_SIZE)
	{
		(elements_count).window_width
			= (elements_count).image_width * (elements_count).width_count;
		(elements_count).window_height
			= (elements_count).image_height * (elements_count).hight_count;
		mlx_set_window_size(window, (elements_count).window_width,
			(elements_count).window_height);
		ft_create_elements_resize(window, elements_count, elements);
		ft_map_to_instance_resize(window, elements,
			elements_count, elements_count.map);
	}
}
