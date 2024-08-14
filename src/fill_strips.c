/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_strips.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:39:08 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/14 18:49:36 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_strip	*last_node_strips(t_strip *node)
{
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}

t_strip	*create_strip_node(t_render data_render)
{
	t_strip	*new;

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

void	init_strips(t_all *all, t_render data_render)
{
	t_strip	*new;
	t_strip	*old;

	old = last_node_strips(all->strip);
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
		if (node->wall == wall && (((node->wall == 'E' || node->wall == 'W')
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

t_strip	*last_wall_node(t_strip *node)
{
	if (!node)
		return (0);
	while (node && node->index != (node->wall_length) - 1)
		node = node->next;
	return (node);
}

t_strip	*first_wall_node(t_strip *node)
{
	if (!node)
		return (0);
	while (node && node->index != 0)
		node = node->previous;
	return (node);
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

static t_render	create_render_data(t_winner final, double intersection_distance,
		double temp_angle)
{
	t_render	data_render;
	char		winner_material;

	winner_material = final.texture;
	data_render.wall_texture = winner_material;
	data_render.floor_height = height(intersection_distance, 'F');
	data_render.ceil_height = height(intersection_distance, 'C');
	data_render.wall_height = WINDOW_HEIGHT - data_render.ceil_height
		- data_render.floor_height;
	data_render.x = (int)(temp_angle / (HAOV / WINDOW_WIDTH));
	data_render.x_winner = final.x_winner;
	data_render.y_winner = final.y_winner;
	return (data_render);
}

static void	create_strip_helper(t_all *all, double temp_angle)
{
	double		ray_angle;
	t_winner	final;
	double		intersection_distance;
	t_render	data_render;

	ray_angle = under_full_circle(all->angle - (HAOV / 2) + temp_angle);
	final = find_winner(all, ray_angle);
	intersection_distance = calculate_distance(all, final, ray_angle,
			temp_angle);
	data_render = create_render_data(final, intersection_distance, temp_angle);
	init_strips(all, data_render);
}

void	create_strips(t_all *all)
{
	double	temp_angle;
	int		counter;

	temp_angle = 0;
	counter = 0;
	all->distance_flag = 0;
	while (counter <= WINDOW_WIDTH)
	{
		create_strip_helper(all, temp_angle);
		counter++;
		temp_angle += (HAOV / WINDOW_WIDTH);
	}
}

void	fill_strips(t_all *all)
{
	create_strips(all);
	fill_index_strips(all);
	fill_length_strips(all);
	update_strips(all);
	fill_number_of_blocks(all);
	strip_to_image(all);
}
