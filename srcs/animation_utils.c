/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:41:20 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/26 12:55:31 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	change_weapon(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (all->active_weapon == 0)
	{
		all->gun->instances[0].enabled = false;
		all->hole->instances[0].enabled = false;
		all->blast->instances[0].enabled = false;
		all->knife->instances[0].enabled = true;
		all->active_weapon = 1;
	}
	else if (all->active_weapon == 1)
	{
		all->knife->instances[0].enabled = false;
		all->gun->instances[0].enabled = true;
		all->hole->instances[0].enabled = true;
		all->active_weapon = 0;
	}
}

void	use_weapon(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	all->gun_used = 1;
	if (all->active_weapon == 0)
		all->gun->instances[0].y = END_GUN_Y;
	else if (all->active_weapon == 1)
	{
		all->knife->instances[0].x = 650;
		all->knife->instances[0].y = 760;
	}
}
