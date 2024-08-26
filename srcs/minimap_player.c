/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:04:59 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/26 16:08:45 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	set_player_position(t_player	*current)
{
	current->image->instances[0].x = MINIMAP_SIDE / 2 + MINIMAP_PADDING
		- current->image->width / 2;
	current->image->instances[0].y = MINIMAP_SIDE / 2 + MINIMAP_PADDING
		- current->image->height / 2;
}

static void	disable_previous_player(t_all *all)
{
	t_player	*current;

	current = all->player_image;
	while (current)
	{
		if (current->image->instances[0].enabled == 1)
		{
			current->image->instances[0].enabled = 0;
			break ;
		}
		current = current->next;
	}
}

static void	activate_current_player(t_all *all)
{
	t_player	*current;

	current = all->player_image;
	while (current)
	{
		if (same(current->angle, all->angle))
		{
			set_player_position(current);
			current->image->instances[0].enabled = 1;
			break ;
		}
		current = current->next;
	}
}

void	enable_correct_player(t_all *all)
{
	disable_previous_player(all);
	activate_current_player(all);
}
