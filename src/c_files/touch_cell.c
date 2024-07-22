/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_cell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:30:37 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/19 16:06:05 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

t_map_data	*ft_find_cell(t_map_data *start, int x, int y, char ch)
{
	t_map_data	*cell;

	cell = start;
	if (ch == '\0')
		while (((*cell).x != x || (*cell).y != y) && cell)
			cell = cell->next;
	else
		while ((*cell).ch != ch && cell)
			cell = cell->next;
	return (cell);
}

void	ft_touch_one_side(t_map_data *start, t_map_data *cell,
	int dx, int dy)
{
	t_map_data	*surround;
	int			x;
	int			y;

	x = (*cell).x + dx;
	y = (*cell).y + dy;
	surround = ft_find_cell(start, x, y, '\0');
	if ((*surround).ch != '1')
		(*surround).t = 1;
}

void	ft_touch_4_side(t_map_data *start, t_map_data *cell)
{
	if ((*cell).ch != '1')
	{
		if ((*cell).ch != '1')
			(*cell).t = 1;
		ft_touch_one_side (start, cell, 1, 0);
		ft_touch_one_side (start, cell, -1, 0);
		ft_touch_one_side (start, cell, 0, 1);
		ft_touch_one_side (start, cell, 0, -1);
	}
}

int	ft_sum_flood(t_map_data *start)
{
	int			count;
	t_map_data	*node;

	node = start;
	count = 0;
	while (node)
	{
		if ((*node).t)
			count++;
		node = node->next;
	}
	return (count);
}

void	ft_flood(t_map_data *start)
{
	t_map_data	*player;
	t_map_data	*node;
	int			sum1;
	int			sum2;

	sum1 = ft_sum_flood(start);
	player = ft_find_cell(start, -1, -1, 'P');
	ft_touch_4_side(start, player);
	sum2 = ft_sum_flood(start);
	while (sum2 > sum1)
	{
		sum1 = ft_sum_flood(start);
		node = start;
		while (node)
		{
			if ((*node).t)
				ft_touch_4_side(start, node);
			node = node->next;
		}
		sum2 = ft_sum_flood(start);
	}
}
