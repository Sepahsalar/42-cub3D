/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_coordinate_ranges.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:58:48 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/21 10:40:49 by nnourine         ###   ########.fr       */
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
	{
		ft_putendl_fd("Not surrounded by walls", 2);
		terminate(all, 1);
	}
	return (min);
}

int	find_max_x(t_all *all, int y)
{
	t_loc	*temp;
	int		max;
	int		found;

	max = 0;
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
	{
		ft_putendl_fd("Not surrounded by walls", 2);
		terminate(all, 1);
	}
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
	{
		ft_putendl_fd("Not surrounded by walls", 2);
		terminate(all, 1);
	}
	return (min);
}

int	find_max_y(t_all *all, int x)
{
	t_loc	*temp;
	int		max;
	int		found;

	found = 0;
	max = 0;
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
	{
		ft_putendl_fd("Not surrounded by walls", 2);
		terminate(all, 1);
	}
	return (max);
}
