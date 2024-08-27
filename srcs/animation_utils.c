/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:41:20 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/27 09:47:30 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	change_weapon(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (all->active_weapon == GUN)
	{
		all->gun->instances[0].enabled = false;
		all->aim->instances[0].enabled = false;
		all->blast->instances[0].enabled = false;
		all->knife->instances[0].enabled = true;
		all->active_weapon = KNIFE;
	}
	else if (all->active_weapon == KNIFE)
	{
		all->knife->instances[0].enabled = false;
		all->gun->instances[0].enabled = true;
		all->aim->instances[0].enabled = true;
		all->active_weapon = GUN;
	}
}

void	use_weapon(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	all->gun_used = 1;
}
