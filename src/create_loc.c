/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_loc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:07:14 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/07 12:26:02 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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
	new->x0 = x;
	new->y0 = y;
	new->x1 = x + 1;
	new->y1 = y + 1;
	new->x_mid = new->x0 + 0.5;
	new->y_mid = new->y0 + 0.5;
	return (new);
}

void	create_loc(t_all *all)
{
	t_loc	*new;
	t_loc	*old;
	char 	*temp;
	int		x;
	int		y;

	all->map->start = NULL;
	temp = all->strmap;
	x = 0;
	y = 0;
	while (*temp)
	{
		if(*temp != '\n')
		{
			new = create_loc_node(*temp, x, y);
			if (!(all->map->start))
					all->map->start = new;
			else
			{
				old->next = new;
				new->previous = old;
			}
			check_failure(0, new, 2, all);
			old = new;
			x++;
		}
		else if (*temp == '\n')
		{
			y++;
			x = 0;
		}
		temp++;
	}
}