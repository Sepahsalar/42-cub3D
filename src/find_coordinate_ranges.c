/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_coordinate_ranges.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:58:48 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/14 18:58:54 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	find_min_x(t_all *all, int y)
{
	t_loc	*temp;
	int		min;

	min = all->map_width;
	temp = all->map->start;
	while (temp)
	{
		if (temp->x < min && temp->y == y)
			min = temp->x;
		temp = temp->next;
	}
	return (min);
}

int	find_max_x(t_all *all, int y)
{
	t_loc	*temp;
	int		max;

	max = 0;
	temp = all->map->start;
	while (temp)
	{
		if (temp->x > max && temp->y == y)
			max = temp->x;
		temp = temp->next;
	}
	return (max);
}

int	find_min_y(t_all *all, int x)
{
	t_loc	*temp;
	int		min;

	min = all->map_height;
	temp = all->map->start;
	while (temp)
	{
		if (temp->y < min && temp->x == x)
			min = temp->y;
		temp = temp->next;
	}
	return (min);
}

int	find_max_y(t_all *all, int x)
{
	t_loc	*temp;
	int		max;

	max = 0;
	temp = all->map->start;
	while (temp)
	{
		if (temp->y > max && temp->x == x)
			max = temp->y;
		temp = temp->next;
	}
	return (max);
}
