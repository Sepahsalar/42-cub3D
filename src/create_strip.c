/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_strip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:39:08 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/12 14:27:54 by nnourine         ###   ########.fr       */
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
		free(node);
		node = temp;
	}
	all->strip = 0;
}

void	init_strip(t_all *all, t_render data_render)
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

// void fill_index_strip(t_all *all)
// {
// 	t_strip *node;
// 	int		index;
// 	char	wall;
// 	double	slope_1;
// 	double	slope_2;
// 	t_strip *temp_a;
// 	t_strip *temp_b;
// 	t_strip *temp_c;
// 	int j = 0;

// 	index = 0;
// 	temp_a = NULL;
// 	temp_b = NULL;
// 	temp_c = NULL;
// 	node = all->strip;
// 	wall = node->wall;
// 	slope_1 = 0;
// 	slope_2 = 0;
// 	while (node)
// 	{
// 		printf("for node : %d ,the index is %d\n", j , index);
// 		printf("slope_1 : %f , slope_2 : %f\n", slope_1, slope_2);
// 		if (temp_a && temp_b && temp_c)
// 		{
// 			slope_1 = temp_b->wall_h - temp_a->wall_h;
// 			slope_2 = temp_c->wall_h - temp_b->wall_h;
// 		}
// 		if (node->wall == wall && (fabs(slope_1 - slope_2) < 100000))
// 			node->index = index;
// 		else
// 		{
// 			wall = node->wall;
// 			index = 0;
// 			temp_a = NULL;
// 			temp_b = NULL;
// 			temp_c = NULL;
// 			slope_1 = 0;
// 			slope_2 = 0;
// 			node->index = index;
// 		}
// 		index++;
// 		j++;
// 		temp_a = node;
// 		if (temp_a)
// 			temp_b = temp_a->next;
// 		else
// 		{
// 			slope_1 = 0;
// 			slope_2 = 0;
// 		}
// 		if (temp_b)
// 			temp_c = temp_b->next;
// 		else
// 		{
// 			slope_1 = 0;
// 			slope_2 = 0;
// 		}
// 		node = node->next;
// 	}
// }

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
