/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loc_visibility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 09:48:29 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/15 13:05:19 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
		loc->consider = 1;
		loc->sn_winner_texture = '0';
		loc->ew_winner_texture = '0';
		loc->sn_winner_x = -1.0;
		loc->sn_winner_y = -1.0;
		loc->ew_winner_x = -1.0;
		loc->ew_winner_y = -1.0;
		loc = loc->next;
	}
}

void	find_winner_surface(t_all *all)
{
	t_loc	*temp;

	temp = all->map->start;
	while (temp)
	{
		if (temp->consider)
		{
			if (temp->sx != -1 && temp->sy != -1)
			{
				temp->sn_winner_distance = sqrt(pow(all->x - temp->sx, 2)
						+ pow(all->y - temp->sy, 2));
				temp->sn_winner_texture = 'S';
				temp->sn_winner_x = temp->sx;
				temp->sn_winner_y = temp->sy;
			}
			if (temp->ex != -1 && temp->ey != -1)
			{
				temp->ew_winner_distance = sqrt(pow(all->x - temp->ex, 2)
						+ pow(all->y - temp->ey, 2));
				temp->ew_winner_texture = 'E';
				temp->ew_winner_x = temp->ex;
				temp->ew_winner_y = temp->ey;
			}
			if ((temp->nx != -1 && temp->ny != -1) && sqrt(pow(all->x
						- temp->nx, 2) + pow(all->y - temp->ny,
						2)) < temp->sn_winner_distance)
			{
				temp->sn_winner_distance = sqrt(pow(all->x - temp->nx, 2)
						+ pow(all->y - temp->ny, 2));
				temp->sn_winner_texture = 'N';
				temp->sn_winner_x = temp->nx;
				temp->sn_winner_y = temp->ny;
			}
			if ((temp->wx != -1 && temp->wy != -1) && sqrt(pow(all->x
						- temp->wx, 2) + pow(all->y - temp->wy,
						2)) < temp->ew_winner_distance)
			{
				temp->ew_winner_distance = sqrt(pow(all->x - temp->wx, 2)
						+ pow(all->y - temp->wy, 2));
				temp->ew_winner_texture = 'W';
				temp->ew_winner_x = temp->wx;
				temp->ew_winner_y = temp->wy;
			}
		}
		temp = temp->next;
	}
}

void	find_visible_surface(t_all *all, t_range range)
{
	t_loc *temp;

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
