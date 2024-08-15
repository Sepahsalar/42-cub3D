/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_general_intersection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:49:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/15 15:38:24 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

static int	ray_hits_ew_surface(t_all *all, double ray_angle, t_loc *temp_pos)
{
	return (temp_pos->ew_winner_texture != '0' && fabs(find_y(ray_angle, all->x,
				all->y, temp_pos->ew_winner_x) - temp_pos->ew_winner_y) <= 0.5);
}

static int	ray_hits_sn_surface(t_all *all, double ray_angle, t_loc *temp_pos)
{
	return (temp_pos->sn_winner_texture != '0' && fabs(find_x(ray_angle, all->x,
				all->y, temp_pos->sn_winner_y) - temp_pos->sn_winner_x) <= 0.5);
}

static int	ew_surface_distance_check(t_loc *winner, t_loc *temp_pos,
		char winner_material)
{
	return (!winner || ((winner_material == winner->ew_winner_texture
				&& temp_pos->ew_winner_distance < winner->ew_winner_distance)
			|| (winner_material == winner->sn_winner_texture
				&& temp_pos->ew_winner_distance < winner->sn_winner_distance)));
}

static int	sn_surface_distance_check(t_loc *winner, t_loc *temp_pos,
		char winner_material)
{
	return (!winner || ((winner_material == winner->ew_winner_texture
				&& temp_pos->sn_winner_distance < winner->ew_winner_distance)
			|| (winner_material == winner->sn_winner_texture
				&& temp_pos->sn_winner_distance < winner->sn_winner_distance)));
}

t_winner	find_general_intersection(t_all *all, double ray_angle)
{
	t_loc		*temp_pos;
	t_winner	final;

	temp_pos = all->map->start;
	final.pos = NULL;
	final.texture = '0';
	while (temp_pos)
	{
		if (ray_hits_ew_surface(all, ray_angle, temp_pos))
			if (ew_surface_distance_check(final.pos, temp_pos, final.texture))
				final = set_final_pos_and_texture(final, temp_pos, 'x');
		if (ray_hits_sn_surface(all, ray_angle, temp_pos))
			if (sn_surface_distance_check(final.pos, temp_pos, final.texture))
				final = set_final_pos_and_texture(final, temp_pos, 'y');
		temp_pos = temp_pos->next;
	}
	final = set_final_x_y_winner(final);
	return (final);
}
