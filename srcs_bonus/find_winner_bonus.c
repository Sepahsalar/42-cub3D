/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_winner_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:23:33 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/29 11:32:13 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

t_winner	set_final_pos_and_texture(t_winner final, t_loc *temp_pos,
		char type)
{
	if (type == 'x')
	{
		final.pos = temp_pos;
		final.texture = final.pos->ew_winner_texture;
	}
	else
	{
		final.pos = temp_pos;
		final.texture = final.pos->sn_winner_texture;
	}
	return (final);
}

t_winner	set_final_x_y_winner(t_winner final)
{
	if (final.texture == final.pos->ew_winner_texture)
		final.x_winner = final.pos->ew_winner_x;
	else
		final.x_winner = final.pos->sn_winner_x;
	if (final.texture == final.pos->ew_winner_texture)
		final.y_winner = final.pos->ew_winner_y;
	else
		final.y_winner = final.pos->sn_winner_y;
	return (final);
}

static t_winner	find_intersection(t_all *all, double ray_angle)
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
	reset_loc(all);
	find_visible_surface(all, range);
	find_winner_surface(all);
	final = find_intersection(all, ray_angle);
	return (final);
}
