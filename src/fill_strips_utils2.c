/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_strips_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:17:43 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/14 19:20:02 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	find_max_index(t_strip *node)
{
	int	max;

	max = 0;
	while (node)
	{
		if (node->index > max)
			max = node->index;
		else
			break ;
		node = node->next;
	}
	return (max + 1);
}

void	fill_length_strips(t_all *all)
{
	t_strip	*node;

	node = all->strip;
	while (node)
	{
		node->wall_length = find_max_index(node);
		node = node->next;
	}
}

void	fill_number_of_blocks(t_all *all)
{
	t_strip	*node;
	t_strip	*start;
	t_strip	*end;

	node = all->strip;
	while (node)
	{
		start = first_wall_node(node);
		end = last_wall_node(node);
		if (same(start->x_winner, end->x_winner))
			node->nb_blocks = fabs(end->y_winner - start->y_winner) + 1;
		else
			node->nb_blocks = fabs(end->x_winner - start->x_winner) + 1;
		node = node->next;
	}
}

void	clean_strips(t_all *all)
{
	t_strip	*node;
	t_strip	*temp;

	node = all->strip;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	all->strip = 0;
}
