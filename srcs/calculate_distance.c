/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_distance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:12:44 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/21 10:40:49 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

double	max_distance(t_all *all)
{
	double	x;
	double	y;

	x = game_size(all, 'x');
	y = game_size(all, 'y');
	return (sqrt(pow(x, 2) + pow(y, 2)));
}

double	find_x(double angle, double x_player, double y_player, double y_target)
{
	double	x_target;

	x_target = ((y_target - y_player) / ft_tan(angle)) + x_player;
	return (x_target);
}

double	find_y(double angle, double x_player, double y_player, double x_target)
{
	double	y_target;

	y_target = ((x_target - x_player) * ft_tan(angle)) + y_player;
	return (y_target);
}

t_winner	calculate_distance(t_all *all, t_winner final, double ray_angle)
{
	t_loc	*winner;
	char	winner_material;

	// double	intersection_distance;
	winner = final.pos;
	winner_material = final.texture;
	if (winner_material == winner->ew_winner_texture)
	{
		final.x_intersection = winner->ew_winner_x;
		final.y_intersection = find_y(ray_angle, all->x, all->y,
				final.x_intersection);
		// intersection_distance = distance(all->x, all->y, winner->ew_winner_x,
		// 		find_y(ray_angle, all->x, all->y, winner->ew_winner_x));
	}
	else
	{
		final.y_intersection = winner->sn_winner_y;
		final.x_intersection = find_x(ray_angle, all->x, all->y,
				final.y_intersection);
		// intersection_distance = distance(all->x, all->y, find_x(ray_angle,
		// 			all->x, all->y, winner->sn_winner_y), winner->sn_winner_y);
	}
	final.intersection_distance = distance(all->x, all->y, final.x_intersection,
			final.y_intersection);
	if (final.intersection_distance < 0.5)
		final.intersection_distance = 0.5;
	final.intersection_distance = final.intersection_distance
		* fabs(ft_cos(all->angle - ray_angle)) + DISTANCE_FROM_WALL;
	// final.intersection_distance = intersection_distance;
	return (final);
}
