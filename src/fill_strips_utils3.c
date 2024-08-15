/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_strips_utils3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:22:17 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/15 14:18:59 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

typedef struct s_current_wall
{
	char	wall;
	int		x_winner;
	int		y_winner;
	int		index;
}			t_current_wall;

int this_node_does_not_belong_to_current_wall(t_strip *node, t_current_wall current_wall)
{
	if ((node->wall == current_wall.wall)
			&& (((node->wall == 'E' || node->wall == 'W') && same(node->x_winner, current_wall.x_winner))
			|| ((node->wall == 'N'	|| node->wall == 'S') && same(node->y_winner, current_wall.y_winner))))
		return (0);
	else
		return (1);
}

t_current_wall	make_this_node_start_of_wall(t_strip *node)
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
	current_wall = make_this_node_start_of_wall(node);
	while (node)
	{
		if (this_node_does_not_belong_to_current_wall(node, current_wall))
			current_wall = make_this_node_start_of_wall(node);
		node->index = current_wall.index;
		current_wall.index++;
		node = node->next;
	}
}

void make_floor_linear(t_all *all)
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

void make_wall_and_ceil_linear(t_all *all)
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
			node->wall_h = (first->wall_h + first->floor_h + (last->wall_h
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
