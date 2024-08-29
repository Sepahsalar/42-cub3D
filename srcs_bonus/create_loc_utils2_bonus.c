/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_loc_utils2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:20:10 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/29 11:32:13 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D_bonus.h"

void	remove_node(t_all *all, t_loc *node)
{
	t_loc	*temp;

	temp = all->map->start;
	while (temp && temp != node)
		temp = temp->next;
	if (temp)
	{
		(temp->previous)->next = temp->next;
		(temp->next)->previous = temp->previous;
		free(temp);
		return ;
	}
}

void	remove_unnecessary_nodes(t_all *all)
{
	t_loc	*temp;
	t_loc	*next_node;

	temp = all->map->start;
	while (temp)
	{
		next_node = temp->next;
		if (temp->c != '1')
			remove_node(all, temp);
		temp = next_node;
	}
}
