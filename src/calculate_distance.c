/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_distance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:12:44 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/14 19:09:30 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

double	calculate_distance(t_all *all, t_winner final, double ray_angle,
		double temp_angle)
{
	t_possible	*winner;
	char		winner_material;
	double		intersection_distance;

	(void)temp_angle;
	winner = final.pos;
	winner_material = final.texture;
	if (winner_material == winner->ew_winner_texture)
		intersection_distance = distance(all->x, all->y, winner->ew_winner_x,
				find_y(ray_angle, all->x, all->y, winner->ew_winner_x));
	else
		intersection_distance = distance(all->x, all->y, find_x(ray_angle,
					all->x, all->y, winner->sn_winner_y), winner->sn_winner_y);
	if (intersection_distance < 0.5)
		intersection_distance = 0.5;
	intersection_distance = intersection_distance * fabs(ft_cos(all->angle
				- ray_angle)) + DISTANCE_FROM_WALL;
	return (intersection_distance);
}
