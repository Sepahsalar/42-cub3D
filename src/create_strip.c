/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_strip.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:39:08 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/13 18:15:56 by asohrabi         ###   ########.fr       */
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
	new->x_winner = data_render.x_winner;
	new->y_winner = data_render.y_winner;
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

// void fill_index_strip(t_all *all)
// {
// 	t_strip *node;
// 	int		index;
// 	char	wall;

// 	index = 0;
// 	node = all->strip;
// 	wall = node->wall;
// 	while (node)
// 	{
// 		if (node->wall == wall)
// 			node->index = index;
// 		else
// 		{
// 			wall = node->wall;
// 			index = 0;
// 			node->index = index;
// 		}
// 		index++;
// 		node = node->next;
// 	}
// }

void fill_index_strip(t_all *all)
{
	t_strip *node;
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
		if (node->wall == wall && (((node->wall == 'E' || node->wall == 'W') && same_double(node->x_winner, x_winner))
				|| ((node->wall == 'N' || node->wall == 'S') && same_double(node->y_winner, y_winner))))
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
	{
		if (node->index == 0)
			printf("start of wall %c is %d\n", node->wall, node->x);
		node = node->next;
	}
}

t_strip *last_wall_node(t_strip *node)
{
	if (!node)
		return (0);
	while (node && node->index != (node->wall_length) - 1)
		node = node->next;
	return (node);
}

t_strip *first_wall_node(t_strip *node)
{
	if (!node)
		return (0);
	while (node && node->index != 0)
		node = node->previous;
	return (node);
}

void update_strips(t_all *all)
{
	t_strip *node;
	t_strip *last;
	t_strip *first;
	int		index;

	node = all->strip;
	while (node)
	{
		if (node->wall_length > 2)
		{
		last = last_wall_node(node);
		first = first_wall_node(node);
		index = node->index;
		node->floor_h = first->floor_h + (last->floor_h - first->floor_h) * ((double)index / (double)last->index);
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
		node->wall_h = (first->wall_h + first->floor_h + (last->wall_h - first->wall_h + last->floor_h - first->floor_h) * ((double)index / (double)last->index)) - node->floor_h;
		node->ceil_h = WINDOW_HEIGHT - node->wall_h - node->floor_h;
		}
		node = node->next;
	}
	// node = all->strip;
	// while (node)
	// {
	// 	last = last_wall_node(node);
	// 	first = first_wall_node(node);
	// 	node->ceil_h = WINDOW_HEIGHT - node->wall_h - node->floor_h;
	// 	node = node->next;
	// }
	// node = all->strip;
	// while (node)
	// {
	// 	last = last_wall_node(node);
	// 	first = first_wall_node(node);
	// 	node->ceil_h = first->ceil_h + (last->ceil_h - first->ceil_h) * (index / last->index);
	// 	node = node->next;
	// }
	// node = all->strip;
	// while (node)
	// {
	// 	last = last_wall_node(node);
	// 	first = first_wall_node(node);
	// 	node->wall_h = WINDOW_HEIGHT - node->ceil_h - node->floor_h;
	// 	node = node->next;
	// }
}


// int find_max_index(t_strip *node)
// {
// 	char wall;
// 	int max;

// 	wall = node->wall;
// 	max = 0;
// 	while (node && node->wall == wall)
// 	{
// 		max = node->index;
// 		node = node->next;
// 	}
// 	return (max + 1);
// }

int find_max_index(t_strip *node)
{
	int max;

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


