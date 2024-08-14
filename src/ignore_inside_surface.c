/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_inside_surface.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:54:47 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/14 18:55:48 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	compare_against_all_nodes(t_all *all, t_loc *temp1)
{
	t_loc	*temp2;

	temp2 = all->map->start;
	if (temp1->c == '1')
	{
		temp2 = all->map->start;
		while (temp2)
		{
			compare_adjacent_walls(temp1, temp2);
			temp2 = temp2->next;
		}
	}
}

void	ignore_upper_wall(t_all *all, t_loc *temp1)
{
	if (temp1->c == '1')
	{
		temp1->nx = -1;
		temp1->ny = -1;
	}
	else
	{
		ft_putendl_fd("Not surrounded by walls", 2);
		terminate(all, 1);
	}
}

void	ignore_lower_wall(t_all *all, t_loc *temp1)
{
	if (temp1->c == '1')
	{
		temp1->sx = -1;
		temp1->sy = -1;
	}
	else
	{
		ft_putendl_fd("Not surrounded by walls", 2);
		terminate(all, 1);
	}
}

void	ignore_outer_walls_up_down(t_all *all)
{
	t_loc	*temp1;
	int		i;
	int		min;
	int		max;

	i = 0;
	while (i < all->map_width)
	{
		min = find_min_y(all, i);
		max = find_max_y(all, i);
		temp1 = all->map->start;
		while (temp1)
		{
			if (temp1->x == i && temp1->y == min)
				ignore_upper_wall(all, temp1);
			else if (temp1->x == i && temp1->y == max)
				ignore_lower_wall(all, temp1);
			temp1 = temp1->next;
		}
		i++;
	}
}

void	ignore_left_wall(t_all *all, t_loc *temp1)
{
	if (temp1->c == '1')
	{
		temp1->wx = -1;
		temp1->wy = -1;
	}
	else
	{
		ft_putendl_fd("Not surrounded by walls", 2);
		terminate(all, 1);
	}
}

void	ignore_right_wall(t_all *all, t_loc *temp1)
{
	if (temp1->c == '1')
	{
		temp1->ex = -1;
		temp1->ey = -1;
	}
	else
	{
		ft_putendl_fd("Not surrounded by walls", 2);
		terminate(all, 1);
	}
}

void	ignore_outer_walls_left_right(t_all *all)
{
	t_loc	*temp1;
	int		i;
	int		min;
	int		max;

	i = 0;
	while (i < all->map_height)
	{
		min = find_min_x(all, i);
		max = find_max_x(all, i);
		temp1 = all->map->start;
		while (temp1)
		{
			if (temp1->y == i && temp1->x == min)
				ignore_left_wall(all, temp1);
			else if (temp1->y == i && temp1->x == max)
				ignore_right_wall(all, temp1);
			temp1 = temp1->next;
		}
		i++;
	}
}

void	ignore_inside_surface(t_all *all)
{
	t_loc	*temp1;

	temp1 = all->map->start;
	while (temp1)
	{
		compare_against_all_nodes(all, temp1);
		temp1 = temp1->next;
	}
	ignore_outer_walls_left_right(all);
	ignore_outer_walls_up_down(all);
}
