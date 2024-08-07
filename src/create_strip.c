/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_strip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:39:08 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/07 12:17:45 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_strip *last_node_strip(t_strip *node)
{
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}

t_strip *create_strip_node(t_render data_render)
{
	t_strip *new;

	new = (t_strip *)malloc(sizeof(t_strip));
	if (!new)
		return (0);
	new->next = 0;
	new->x = data_render.x;
	new->ceil_h = data_render.ceil_height;
	new->floor_h = data_render.floor_height;
	new->wall_h = data_render.wall_height;
	new->wall = data_render.wall_texture;
	new->index = 0;
	new->wall_length = 0;
	new->image = 0;
	new->next = 0;
	new->previous = 0;
	return (new);
}

void clean_strip(t_all *all)
{
	t_strip *node;
	t_strip *temp;

	node = all->strip;
	while (node)
	{
		temp = node->next;
		mlx_delete_image(all->window, node->image);
		free(node);
		node = temp;
	}
}

void	create_strip(t_all *all, t_render data_render)
{
	t_strip	*new;
	t_strip	*old;

	old = last_node_strip(all->strip);
	new = create_strip_node(data_render);
	if (!old)
			all->strip = new;
	else
	{
		old->next = new;
		new->previous = old;
	}
	check_failure(0, new, 2, all);
}

void fill_index_strip(t_all *all)
{
	t_strip *node;
	int		index;
	char	wall;

	index = 0;
	node = all->strip;
	wall = node->wall;
	while (node)
	{
		if (node->wall == wall)
			node->index = index;
		else
		{
			wall = node->wall;
			index = 0;
			node->index = index;
		}
		index++;
		node = node->next;
	}
}

int find_max_index(t_strip *node)
{
	char wall;
	int max;

	wall = node->wall;
	max = 0;
	while (node && node->wall == wall)
	{
		max = node->index;
		node = node->next;
	}
	return (max + 1);
}

void fill_length_strip(t_all *all)
{
	t_strip *node;

	node = all->strip;
	while (node)
	{
		node->wall_length = find_max_index(node);
		node = node->next;
	}
}