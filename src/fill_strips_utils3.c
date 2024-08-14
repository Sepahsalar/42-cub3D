/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_strips_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:22:17 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/14 19:33:32 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	fill_index_strips(t_all *all)
{
	t_strip	*node;
	int		index;
	char	wall;
	int		x_winner;
	int		y_winner;

	index = 0;
	node = all->strip;
	wall = node->wall;
	x_winner = node->x_winner;
	y_winner = node->y_winner;
	while (node)
	{
		if (node->wall == wall
			&& (((node->wall == 'E' || node->wall == 'W')
					&& same(node->x_winner, x_winner))
				|| ((node->wall == 'N' || node->wall == 'S')
					&& same(node->y_winner, y_winner))))
			node->index = index;
		else
		{
			wall = node->wall;
			x_winner = node->x_winner;
			y_winner = node->y_winner;
			index = 0;
			node->index = index;
		}
		index++;
		node = node->next;
	}
	node = all->strip;
	while (node)
		node = node->next;
}

void	update_strips(t_all *all)
{
	t_strip	*node;
	t_strip	*last;
	t_strip	*first;
	int		index;

	node = all->strip;
	while (node)
	{
		if (node->wall_length > 2)
		{
			last = last_wall_node(node);
			first = first_wall_node(node);
			index = node->index;
			node->floor_h = first->floor_h + (last->floor_h - first->floor_h)
				* ((double)index / (double)last->index);
		}
		node = node->next;
	}
	node = all->strip;
	while (node)
	{
		if (node->wall_length > 2)
		{
			last = last_wall_node(node);
			first = first_wall_node(node);
			index = node->index;
			node->wall_h = (first->wall_h + first->floor_h + (last->wall_h
						- first->wall_h + last->floor_h - first->floor_h)
					* ((double)index / (double)last->index)) - node->floor_h;
			node->ceil_h = WINDOW_HEIGHT - node->wall_h - node->floor_h;
		}
		node = node->next;
	}
}
