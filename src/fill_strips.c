/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_strips.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:39:08 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/15 13:08:32 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static t_render	create_render_data(t_winner final, double intersection_distance,
		double temp_angle)
{
	t_render	data_render;
	char		winner_material;

	winner_material = final.texture;
	data_render.wall_texture = winner_material;
	data_render.floor_height = height(intersection_distance, 'F');
	data_render.ceil_height = height(intersection_distance, 'C');
	data_render.wall_height = WINDOW_HEIGHT - data_render.ceil_height
		- data_render.floor_height;
	data_render.x = (int)(temp_angle / (HAOV / WINDOW_WIDTH));
	data_render.x_winner = final.x_winner;
	data_render.y_winner = final.y_winner;
	return (data_render);
}

static void	create_strips_helper(t_all *all, double temp_angle)
{
	double		ray_angle;
	t_winner	final;
	double		intersection_distance;
	t_render	data_render;

	ray_angle = under_full_circle(all->angle - (HAOV / 2) + temp_angle);
	final = find_winner(all, ray_angle);
	intersection_distance = calculate_distance(all, final, ray_angle);
	data_render = create_render_data(final, intersection_distance, temp_angle);
	init_strips(all, data_render);
}

static void	create_strips(t_all *all)
{
	double	temp_angle;
	int		counter;

	temp_angle = 0;
	counter = 0;
	all->distance_flag = 0;
	while (counter <= WINDOW_WIDTH)
	{
		create_strips_helper(all, temp_angle);
		counter++;
		temp_angle += (HAOV / WINDOW_WIDTH);
	}
}

void	fill_strips(t_all *all)
{
	create_strips(all);
	fill_index_strips(all);
	fill_length_strips(all);
	update_strips(all);
	fill_number_of_blocks(all);
	strip_to_image(all);
}
