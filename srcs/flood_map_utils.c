/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 11:00:57 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/29 12:27:05 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static int	find_min_x_wet(t_all *all, int y)
{
	t_loc	*temp;
	int		min;
	int		found;

	found = 0;
	min = MAX_NODE;
	temp = all->map->start;
	while (temp)
	{
		if (temp->x < min && temp->y == y && temp->wet == 1)
		{
			min = temp->x;
			found = 1;
		}
		temp = temp->next;
	}
	if (!found)
		terminate(all, "Map is separated", NULL, NULL);
	return (min);
}

static int	find_max_x_wet(t_all *all, int y)
{
	t_loc	*temp;
	int		max;
	int		found;

	max = -1;
	found = 0;
	temp = all->map->start;
	while (temp)
	{
		if (temp->x > max && temp->y == y && temp->wet == 1)
		{
			max = temp->x;
			found = 1;
		}
		temp = temp->next;
	}
	if (!found)
		terminate(all, "Map is separated", NULL, NULL);
	return (max);
}

int	node_is_inside(t_all *all, t_loc *loc)
{
	if (loc->x > find_min_x_wet(all, loc->y)
		&& loc->x < find_max_x_wet(all, loc->y))
		return (1);
	return (0);
}
