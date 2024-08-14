/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_winner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:23:33 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/14 18:23:45 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_winner	find_general_intersection(t_all *all, double ray_angle)
{
	t_possible	*temp_pos;
	t_possible	*winner;
	t_winner	final;
	char		winner_material;

	temp_pos = all->possible;
	winner = NULL;
	winner_material = '0';
	while (temp_pos)
	{
		if (temp_pos->ew_winner_texture != '0' && fabs(find_y(ray_angle, all->x,
					all->y, temp_pos->ew_winner_x)
				- temp_pos->ew_winner_y) <= 0.5)
		{
			if (!winner || ((winner_material == winner->ew_winner_texture
						&& temp_pos->ew_winner_distance < winner->ew_winner_distance)
					|| (winner_material == winner->sn_winner_texture
						&& temp_pos->ew_winner_distance < winner->sn_winner_distance)))
			{
				winner = temp_pos;
				winner_material = winner->ew_winner_texture;
			}
		}
		if (temp_pos->sn_winner_texture != '0' && fabs(find_x(ray_angle, all->x,
					all->y, temp_pos->sn_winner_y)
				- temp_pos->sn_winner_x) <= 0.5)
		{
			if (!winner || ((winner_material == winner->ew_winner_texture
						&& temp_pos->sn_winner_distance < winner->ew_winner_distance)
					|| (winner_material == winner->sn_winner_texture
						&& temp_pos->sn_winner_distance < winner->sn_winner_distance)))
			{
				winner = temp_pos;
				winner_material = winner->sn_winner_texture;
			}
		}
		temp_pos = temp_pos->next;
	}
	final.pos = winner;
	final.texture = winner_material;
	if (winner_material == winner->ew_winner_texture)
		final.x_winner = winner->ew_winner_x;
	else
		final.x_winner = winner->sn_winner_x;
	if (winner_material == winner->ew_winner_texture)
		final.y_winner = winner->ew_winner_y;
	else
		final.y_winner = winner->sn_winner_y;
	return (final);
}

t_winner	find_specific_intersection(t_all *all, double ray_angle, char flag)
{
	t_possible	*temp_pos;
	t_possible	*winner;
	char		winner_material;
	t_winner	final;

	temp_pos = all->possible;
	winner = NULL;
	winner_material = '0';
	if (same(ray_angle, 270.0) || same(ray_angle, 90.0))
	{
		while (temp_pos)
		{
			if (temp_pos->sn_winner_texture == flag
				&& same(temp_pos->sn_winner_x, all->x))
				if (!winner
					|| (temp_pos->sn_winner_distance < winner->sn_winner_distance))
					winner = temp_pos;
			temp_pos = temp_pos->next;
		}
		winner_material = flag;
	}
	else if (same(ray_angle, 0.0) || same(ray_angle, 180.0))
	{
		while (temp_pos)
		{
			if (temp_pos->ew_winner_texture == flag
				&& same(temp_pos->ew_winner_y, all->y))
				if (!winner
					|| (temp_pos->ew_winner_distance < winner->ew_winner_distance))
					winner = temp_pos;
			temp_pos = temp_pos->next;
		}
		winner_material = flag;
	}
	final.pos = winner;
	final.texture = winner_material;
	if (winner_material == winner->ew_winner_texture)
		final.x_winner = winner->ew_winner_x;
	else
		final.x_winner = winner->sn_winner_x;
	if (winner_material == winner->ew_winner_texture)
		final.y_winner = winner->ew_winner_y;
	else
		final.y_winner = winner->sn_winner_y;
	return (final);
}

t_winner	find_intersection(t_all *all, double ray_angle)
{
	t_winner	final;

	if (same(ray_angle, 270.0))
		final = find_specific_intersection(all, ray_angle, 'S');
	else if (same(ray_angle, 90.0))
		final = find_specific_intersection(all, ray_angle, 'N');
	else if (same(ray_angle, 0.0))
		final = find_specific_intersection(all, ray_angle, 'W');
	else if (same(ray_angle, 180.0))
		final = find_specific_intersection(all, ray_angle, 'E');
	else
		final = find_general_intersection(all, ray_angle);
	return (final);
}

t_winner	find_winner(t_all *all, double ray_angle)
{
	t_range		range;
	t_winner	final;

	range.x_min = min_x(all->x, ray_angle);
	range.x_max = max_x(all->x, all->map_width, ray_angle);
	range.y_min = min_y(all->y, ray_angle);
	range.y_max = max_y(all->y, all->map_height, ray_angle);
	create_possibility(all, range);
	find_winner_surface(all);
	final = find_intersection(all, ray_angle);
	clean_possibility(all->possible);
	all->possible = NULL;
	return (final);
}