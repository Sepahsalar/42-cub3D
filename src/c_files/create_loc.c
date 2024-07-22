/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_loc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 11:07:14 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/22 17:37:03 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"


t_loc	*clean_loc(t_loc *first)
{
	t_loc	*node;
	t_loc	*temp;

	node = first;
	while (node)
	{
		temp = node->next;
		clean_cmd_node(node);
		node = temp;
	}
	return (0);
}

t_loc	*create_loc_node(char *temp, int x, int y, int z)
{
	t_loc			*new;

	new = malloc(sizeof(t_loc));
	if (!new)
		return (0);
	ft_memset(new, 0, sizeof(t_loc));3
	
	
	new->c = *temp;
	new->x = x;
	new->y = y;
	new->z = z;
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
	while (temp)
	{
		if(*temp != '\n')
		{
			new = create_loc_node(temp, x, y, 0);
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
