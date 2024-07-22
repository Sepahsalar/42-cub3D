/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_character_size.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 13:22:07 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/19 17:29:58 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_get_monitor_size(int *monitor_width, int *monitor_height)
{
	mlx_t		*temp_window;

	temp_window = mlx_init(100, 100, "temp_window", true);
	if (!temp_window)
		ft_exit_failure(0, 0, "Problem in getting the monitor size");
	mlx_get_monitor_size(0, monitor_width, monitor_height);
	mlx_terminate(temp_window);
}

float	ft_get_ratio(int size, int count)
{
	float	ratio;

	ratio = size / START_IMAGE_SIZE;
	ratio = ratio / count;
	return (ratio);
}

float	ft_best_ratio(float ratio_width, float ratio_height)
{
	float	final_ratio;

	final_ratio = ratio_height;
	if (ratio_width < final_ratio)
		final_ratio = ratio_width;
	if (final_ratio > 1)
		final_ratio = 1;
	return (final_ratio);
}

void	ft_calculate_character_size(t_elements_count *elements_count)
{
	int			monitor_width;
	int			monitor_height;
	float		ratio_width;
	float		final_ratio;

	(*elements_count).start_image_size = START_IMAGE_SIZE;
	ft_get_monitor_size(&monitor_width, &monitor_height);
	monitor_width = floor(monitor_width * MAX_MONITOR_USAGE);
	monitor_height = floor(monitor_height * MAX_MONITOR_USAGE);
	ratio_width = ft_get_ratio(monitor_width, (*elements_count).width_count);
	if (MIN_IMAGE_SIZE > (ratio_width * START_IMAGE_SIZE))
		ft_exit_failure(0, 0,
			"The width of the map is too big for this monitor");
	final_ratio = ft_get_ratio(monitor_height, (*elements_count).hight_count);
	if (MIN_IMAGE_SIZE > (final_ratio * START_IMAGE_SIZE))
		ft_exit_failure(0, 0,
			"The height of the map is too big for this monitor");
	final_ratio = ft_best_ratio(ratio_width, final_ratio);
	(*elements_count).image_width = floor(final_ratio * START_IMAGE_SIZE);
	(*elements_count).image_height = floor(final_ratio * START_IMAGE_SIZE);
	(*elements_count).window_width = ceil((*elements_count).image_width
			* (*elements_count).width_count);
	(*elements_count).window_height = ceil((*elements_count).image_height
			* (*elements_count).hight_count);
}
