/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_strips_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:17:43 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/29 12:26:56 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	find_max_index(t_strip *node)
{
	int	max;

	max = -1;
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
