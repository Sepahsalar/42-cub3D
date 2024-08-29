/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_loc_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 19:02:20 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/29 11:32:13 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

t_loc	*clean_loc(t_loc *first)
{
	t_loc	*node;
	t_loc	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	return (0);
}

static void	init_surface(t_loc *new)
{
	if (new->c != '1')
	{
		new->sx = -1;
		new->sy = -1;
		new->ex = -1;
		new->ey = -1;
		new->wx = -1;
		new->wy = -1;
		new->nx = -1;
		new->ny = -1;
	}
	else
	{
		new->sx = new->x + 0.5;
		new->sy = new->y + 1.0;
		new->wx = new->x;
		new->wy = new->y + 0.5;
		new->ex = new->x + 1.0;
		new->ey = new->y + 0.5;
		new->nx = new->x + 0.5;
		new->ny = new->y;
	}
}

t_loc	*create_loc_node(char temp, int x, int y)
{
	t_loc	*new;

	new = malloc(sizeof(t_loc));
	if (!new)
		return (0);
	ft_memset(new, 0, sizeof(t_loc));
	new->c = temp;
	new->x = x;
	new->y = y;
	init_surface(new);
	return (new);
}

void	update_coordinate(t_coordinate *coordinate, char *temp)
{
	if (*temp != '\n')
		coordinate->x++;
	else
	{
		coordinate->y++;
		coordinate->x = 0;
	}
}

void	link_new_node(t_all *all, t_loc *new, t_loc *old)
{
	if (!(all->map->start))
		all->map->start = new;
	else
	{
		old->next = new;
		new->previous = old;
	}
	if (!new)
		terminate(all, "Allocating memory failed", NULL, NULL);
}
