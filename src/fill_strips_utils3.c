/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_strips_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:22:17 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/19 12:13:28 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	make_floor_linear(t_all *all)
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
}

void	make_wall_and_ceil_linear(t_all *all)
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
			node->wall_h = ((first->wall_h + first->floor_h) + (last->wall_h
						- first->wall_h + last->floor_h - first->floor_h)
					* ((double)index / (double)last->index)) - node->floor_h;
			node->ceil_h = WINDOW_HEIGHT - node->wall_h - node->floor_h;
		}
		node = node->next;
	}
}

void	update_strips(t_all *all)
{
	make_floor_linear(all);
	make_wall_and_ceil_linear(all);
}
