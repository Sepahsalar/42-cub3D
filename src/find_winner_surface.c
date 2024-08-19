/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_winner_surface.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:03:45 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/15 15:42:11 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	north_is_better_than_south(t_all *all, t_loc *temp)
{
	return ((temp->nx != -1 && temp->ny != -1) && sqrt(pow(all->x - temp->nx, 2)
			+ pow(all->y - temp->ny, 2)) < temp->sn_winner_distance);
}

int	west_is_better_than_east(t_all *all, t_loc *temp)
{
	return ((temp->wx != -1 && temp->wy != -1) && sqrt(pow(all->x - temp->wx, 2)
			+ pow(all->y - temp->wy, 2)) < temp->ew_winner_distance);
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
				south_wins(all, temp);
			if (temp->ex != -1 && temp->ey != -1)
				east_wins(all, temp);
			if (north_is_better_than_south(all, temp))
				north_wins(all, temp);
			if (west_is_better_than_east(all, temp))
				west_wins(all, temp);
		}
		temp = temp->next;
	}
}
