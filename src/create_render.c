/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:39:08 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/07 11:28:15 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char texture_finder(int y, t_render data_render)
{
	if (y < data_render.ceil_height)
		return ('C');
	else if (y <= (data_render.wall_height + data_render.ceil_height))
		return (data_render.wall_texture);
	else
		return ('F');
}

t_loc *last_node(t_loc *node)
{
	if (!node)
		return (0);
	while (node->next)
		node = node->next;
	return (node);
}

void	create_render(t_all *all, t_render data_render)
{
	t_loc	*new;
	t_loc	*old;
	int		y;

	old = last_node(all->render);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		new = create_loc_node(texture_finder(y, data_render), data_render.x, y);
		if (!old)
				all->render = new;
		else
		{
			old->next = new;
			new->previous = old;
		}
		check_failure(0, new, 2, all);
		old = new;
		y++;
	}
}