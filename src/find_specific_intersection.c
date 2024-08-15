/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_specific_intersection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:27:08 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/15 13:27:32 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static t_winner	find_specific_intersection_vertical(t_all *all, char flag)
{
	t_loc		*temp_pos;
	t_winner	final;

	temp_pos = all->map->start;
	final.pos = NULL;
	final.texture = '0';
	while (temp_pos)
	{
		if (temp_pos->sn_winner_texture == flag && same(temp_pos->sn_winner_x,
				all->x))
			if (!final.pos
				|| (temp_pos->sn_winner_distance < final.pos->sn_winner_distance))
				final.pos = temp_pos;
		temp_pos = temp_pos->next;
	}
	final.texture = flag;
	final = set_final_x_y_winner(final);
	return (final);
}

static t_winner	find_specific_intersection_horizental(t_all *all, char flag)
{
	t_loc		*temp_pos;
	t_winner	final;

	temp_pos = all->map->start;
	final.pos = NULL;
	final.texture = '0';
	while (temp_pos)
	{
		if (temp_pos->ew_winner_texture == flag && same(temp_pos->ew_winner_y,
				all->y))
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
