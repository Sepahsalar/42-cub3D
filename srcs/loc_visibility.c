/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loc_visibility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:48:29 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/27 09:36:27 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	reset_loc(t_all *all)
{
	t_loc	*loc;

	loc = all->map->start;
	while (loc)
	{
		loc->sn_winner_distance = all->max_distance;
		loc->ew_winner_distance = all->max_distance;
		if (loc->sx != -1 || loc->ex != -1 || loc->nx != -1 || loc->wx != -1)
			loc->consider = 1;
		else
			loc->consider = 0;
		loc->sn_winner_texture = '0';
		loc->ew_winner_texture = '0';
		loc->sn_winner_x = -1.0;
		loc->sn_winner_y = -1.0;
		loc->ew_winner_x = -1.0;
		loc->ew_winner_y = -1.0;
		loc = loc->next;
	}
}

void	find_visible_surface(t_all *all, t_range range)
{
	t_loc	*temp;

	temp = all->map->start;
	while (temp)
	{
		if (temp->consider)
		{
			if (temp->x < range.x_min || temp->x > range.x_max
				|| temp->y < range.y_min || temp->y > range.y_max)
				temp->consider = 0;
		}
		temp = temp->next;
	}
}
