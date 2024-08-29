/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_coordinate_ranges.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:58:48 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/29 12:26:58 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	find_min_x(t_all *all, int y)
{
	t_loc	*temp;
	int		min;
	int		found;

	found = 0;
	min = all->map_width;
	temp = all->map->start;
	while (temp)
	{
		if (temp->x < min && temp->y == y)
		{
			min = temp->x;
			found = 1;
		}
		temp = temp->next;
	}
	if (!found)
		terminate(all, "Not surrounded by walls", NULL, NULL);
	return (min);
}

int	find_max_x(t_all *all, int y)
{
	t_loc	*temp;
	int		max;
	int		found;

	max = -1;
	found = 0;
	temp = all->map->start;
	while (temp)
	{
		if (temp->x > max && temp->y == y)
		{
			max = temp->x;
			found = 1;
		}
		temp = temp->next;
	}
	if (!found)
		terminate(all, "Not surrounded by walls", NULL, NULL);
	return (max);
}

int	find_min_y(t_all *all, int x)
{
	t_loc	*temp;
	int		min;
	int		found;

	min = all->map_height;
	found = 0;
	temp = all->map->start;
	while (temp)
	{
		if (temp->y < min && temp->x == x)
		{
			min = temp->y;
			found = 1;
		}
		temp = temp->next;
	}
	if (!found)
		terminate(all, "Not surrounded by walls", NULL, NULL);
	return (min);
}

int	find_max_y(t_all *all, int x)
{
	t_loc	*temp;
	int		max;
	int		found;

	found = 0;
	max = -1;
	temp = all->map->start;
	while (temp)
	{
		if (temp->y > max && temp->x == x)
		{
			max = temp->y;
			found = 1;
		}
		temp = temp->next;
	}
	if (!found)
		terminate(all, "Not surrounded by walls", NULL, NULL);
	return (max);
}
