/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_winner_surface_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:05:56 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/15 15:06:13 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	south_wins(t_all *all, t_loc *temp)
{
	temp->sn_winner_distance = sqrt(pow(all->x - temp->sx, 2)
			+ pow(all->y - temp->sy, 2));
	temp->sn_winner_texture = 'S';
	temp->sn_winner_x = temp->sx;
	temp->sn_winner_y = temp->sy;
}

void	east_wins(t_all *all, t_loc *temp)
{
	temp->ew_winner_distance = sqrt(pow(all->x - temp->ex, 2)
			+ pow(all->y - temp->ey, 2));
	temp->ew_winner_texture = 'E';
	temp->ew_winner_x = temp->ex;
	temp->ew_winner_y = temp->ey;
}

void	north_wins(t_all *all, t_loc *temp)
{
	temp->sn_winner_distance = sqrt(pow(all->x - temp->nx, 2)
			+ pow(all->y - temp->ny, 2));
	temp->sn_winner_texture = 'N';
	temp->sn_winner_x = temp->nx;
	temp->sn_winner_y = temp->ny;
}

void	west_wins(t_all *all, t_loc *temp)
{
	temp->ew_winner_distance = sqrt(pow(all->x - temp->wx, 2)
			+ pow(all->y - temp->wy, 2));
	temp->ew_winner_texture = 'W';
	temp->ew_winner_x = temp->wx;
	temp->ew_winner_y = temp->wy;
}
