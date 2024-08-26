/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 09:27:21 by nnourine          #+#    #+#             */
/*   Updated: 2024/08/26 12:50:23 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	start_timer(t_all *all)
{
	if (all->animation_started == 0)
	{
		all->time1 = ft_timestamp_milis(all);
		all->animation_started = 1;
	}
}

void	end_animation(t_all *all)
{
	all->gun_used = 0;
	all->animation_started = 0;
}

void	gun_animation(t_all *all)
{
	start_timer(all);
	all->time2 = ft_timestamp_milis(all);
	if (all->time2 > all->time1 + 500 && all->active_weapon == 0)
	{
		all->gun->instances[0].y = START_GUN_Y;
		end_animation(all);
	}
	else if (all->time2 > all->time1 + 400 && all->active_weapon == 0)
		all->blast->instances[0].enabled = false;
	else if (all->time2 > all->time1 + 250)
	{
		all->gun->instances[0].x = START_GUN_X;
		all->blast->instances[0].enabled = true;
	}
	else if (all->time2 > all->time1 + 200 && all->active_weapon == 0)
		all->gun->instances[0].x = START_GUN_X + 50;
}

void	knife_animation(t_all *all)
{
	start_timer(all);
	all->time2 = ft_timestamp_milis(all);
	if (all->time2 > all->time1 + 200 && all->active_weapon == 1)
	{
		all->knife->instances[0].x = 700;
		all->knife->instances[0].y = 810;
		end_animation(all);
	}
}

void	animation(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (all->gun_used)
	{
		if (all->active_weapon == 1)
			knife_animation(all);
		else if (all->active_weapon == 0)
			gun_animation(all);
	}
}
