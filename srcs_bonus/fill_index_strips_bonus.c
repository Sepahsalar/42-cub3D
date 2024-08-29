/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_index_strips_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 14:50:05 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/29 11:32:13 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

static int	node_belongs_to_wall(t_strip *node, t_current_wall current_wall)
{
	if ((node->wall == current_wall.wall) && (((node->wall == 'E'
					|| node->wall == 'W') && same(node->x_winner,
					current_wall.x_winner)) || ((node->wall == 'N'
					|| node->wall == 'S') && same(node->y_winner,
					current_wall.y_winner))))
		return (0);
	else
		return (1);
}

static t_current_wall	set_wall_start_node(t_strip *node)
{
	t_current_wall	current_wall;

	current_wall.wall = node->wall;
	current_wall.x_winner = node->x_winner;
	current_wall.y_winner = node->y_winner;
	current_wall.index = 0;
	return (current_wall);
}

void	fill_index_strips(t_all *all)
{
	t_strip			*node;
	t_current_wall	current_wall;

	node = all->strip;
	current_wall = set_wall_start_node(node);
	while (node)
	{
		if (node_belongs_to_wall(node, current_wall))
			current_wall = set_wall_start_node(node);
		node->index = current_wall.index;
		current_wall.index++;
		node = node->next;
	}
}
