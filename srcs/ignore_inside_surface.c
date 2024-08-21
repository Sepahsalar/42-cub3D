/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_inside_surface.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:54:47 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/21 10:40:49 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	compare_against_all_nodes(t_all *all, t_loc *temp1)
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

static void	ignore_outer_walls_up_down(t_all *all)
{
	t_loc	*temp;
	int		i;
	int		min;
	int		max;

	i = 0;
	while (i < all->map_width)
	{
		min = find_min_y(all, i);
		max = find_max_y(all, i);
		temp = all->map->start;
		while (temp)
		{
			if (temp->x == i && temp->y == min)
				ignore_upper_wall(all, temp);
			else if (temp->x == i && temp->y == max)
				ignore_lower_wall(all, temp);
			temp = temp->next;
		}
		i++;
	}
}

static void	ignore_outer_walls_left_right(t_all *all)
{
	t_loc	*temp;
	int		i;
	int		min;
	int		max;

	i = 0;
	while (i < all->map_height)
	{
		min = find_min_x(all, i);
		max = find_max_x(all, i);
		temp = all->map->start;
		while (temp)
		{
			if (temp->y == i && temp->x == min)
				ignore_left_wall(all, temp);
			else if (temp->y == i && temp->x == max)
				ignore_right_wall(all, temp);
			temp = temp->next;
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
