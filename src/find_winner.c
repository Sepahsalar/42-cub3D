/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_winner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:23:33 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/14 19:43:58 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int does_ray_angle_passes_ew_surface(t_all *all, double ray_angle, t_possible *temp_pos)
{
	return (temp_pos->ew_winner_texture != '0' && fabs(find_y(ray_angle, all->x,
					all->y, temp_pos->ew_winner_x)
				- temp_pos->ew_winner_y) <= 0.5);
}

int is_this_ew_surface_closer(t_possible *winner, t_possible *temp_pos, char winner_material)
{
	return (!winner || ((winner_material == winner->ew_winner_texture
						&& temp_pos->ew_winner_distance < winner->ew_winner_distance)
					|| (winner_material == winner->sn_winner_texture
						&& temp_pos->ew_winner_distance < winner->sn_winner_distance)));
}

int does_ray_angle_passes_sn_surface(t_all *all, double ray_angle, t_possible *temp_pos)
{
	return (temp_pos->sn_winner_texture != '0' && fabs(find_x(ray_angle, all->x,
					all->y, temp_pos->sn_winner_y)
				- temp_pos->sn_winner_x) <= 0.5);
}

int is_this_sn_surface_closer(t_possible *winner, t_possible *temp_pos, char winner_material)
{
	return (!winner || ((winner_material == winner->ew_winner_texture
						&& temp_pos->sn_winner_distance < winner->ew_winner_distance)
					|| (winner_material == winner->sn_winner_texture
						&& temp_pos->sn_winner_distance < winner->sn_winner_distance)));
}

t_winner	set_final_pos_and_texture(t_winner final, t_possible *temp_pos, char type)
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

t_winner	find_general_intersection(t_all *all, double ray_angle)
{
	t_possible	*temp_pos;
	t_winner	final;

	temp_pos = all->possible;
	final.pos = NULL;
	final.texture = '0';
	while (temp_pos)
	{
		if (does_ray_angle_passes_ew_surface(all, ray_angle, temp_pos))
		{
			if (is_this_ew_surface_closer(final.pos, temp_pos, final.texture))
				final = set_final_pos_and_texture(final, temp_pos, 'x');
		}
		if (does_ray_angle_passes_sn_surface(all, ray_angle, temp_pos))
		{
			if (is_this_sn_surface_closer(final.pos, temp_pos, final.texture))
				final = set_final_pos_and_texture(final, temp_pos, 'y');
		}
		temp_pos = temp_pos->next;
	}
	final = set_final_x_y_winner(final);
	return (final);
}

t_winner	find_specific_intersection_vertical(t_all *all, char flag)
{
	t_possible	*temp_pos;
	t_winner	final;

	temp_pos = all->possible;
	final.pos = NULL;
	final.texture = '0';
	while (temp_pos)
	{
		if (temp_pos->sn_winner_texture == flag
			&& same(temp_pos->sn_winner_x, all->x))
			if (!final.pos
				|| (temp_pos->sn_winner_distance < final.pos->sn_winner_distance))
				final.pos = temp_pos;
		temp_pos = temp_pos->next;
	}
	final.texture = flag;
	final = set_final_x_y_winner(final);
	return (final);
}

t_winner	find_specific_intersection_horizental(t_all *all, char flag)
{
	t_possible	*temp_pos;
	t_winner	final;

	temp_pos = all->possible;
	final.pos = NULL;
	final.texture = '0';
	while (temp_pos)
	{
		if (temp_pos->ew_winner_texture == flag
			&& same(temp_pos->ew_winner_y, all->y))
			if (!final.pos
				|| (temp_pos->ew_winner_distance < final.pos->ew_winner_distance))
				final.pos = temp_pos;
		temp_pos = temp_pos->next;
	}
	final.texture = flag;
	final = set_final_x_y_winner(final);
	return (final);
}


t_winner	find_specific_intersection(t_all *all, double ray_angle, char flag)
{
	if (same(ray_angle, 270.0) || same(ray_angle, 90.0))
		return (find_specific_intersection_vertical(all, flag));
	else
		return (find_specific_intersection_horizental(all, flag));
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
