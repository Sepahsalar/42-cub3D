/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:54:25 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/29 11:01:23 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	wet_loc(t_all *all, t_loc *loc)
{
	int		x;
	int		y;
	t_loc	*temp;

	x = loc->x;
	y = loc->y;
	temp = all->map->start;
	while (temp)
	{
		if ((temp->x == x && temp->y == y + 1)
			|| (temp->x == x && temp->y == y - 1)
			|| (temp->x == x + 1 && temp->y == y)
			|| (temp->x == x - 1 && temp->y == y))
			temp->wet = 1;
		temp = temp->next;
	}
}

int	sum_wet(t_all *all)
{
	t_loc	*loc;
	int		sum;

	loc = all->map->start;
	sum = 0;
	while (loc)
	{
		if (loc->wet == 1)
			sum++;
		loc = loc->next;
	}
	return (sum);
}

void	check_dry(t_all *all)
{
	t_loc	*loc;

	loc = all->map->start;
	while (loc)
	{
		if (loc->wet == 0 && !node_is_inside(all, loc))
			terminate(all, "Map is separated", NULL, NULL);
		loc = loc->next;
	}
}

void	flood_map(t_all *all)
{
	t_loc	*loc;
	int		sum1;
	int		sum2;

	all->map->start->wet = 1;
	wet_loc(all, all->map->start);
	sum1 = 0;
	sum2 = sum_wet(all);
	while (sum1 < sum2)
	{
		loc = all->map->start;
		while (loc)
		{
			if (loc->wet == 1)
				wet_loc(all, loc);
			loc = loc->next;
		}
		loc = all->map->start;
		sum1 = sum2;
		sum2 = sum_wet(all);
	}
}
