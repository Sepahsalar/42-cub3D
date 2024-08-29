/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asohrabi <asohrabi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:23:58 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/29 12:27:40 by asohrabi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double	under_full_circle(double angle)
{
	if (angle >= FULL_CIRCLE_DEGREES)
		return (angle -= FULL_CIRCLE_DEGREES);
	if (angle < 0)
		return (angle += FULL_CIRCLE_DEGREES);
	return (angle);
}

void	turn_press(void *param, char c)
{
	t_all	*all;

	all = (t_all *)param;
	clean_strips(all);
	mlx_delete_image(all->window, all->image);
	if (c == 'R')
		all->angle += TURN_INTERVAL;
	else
		all->angle -= TURN_INTERVAL;
	all->angle = under_full_circle(all->angle);
	fill_strips(all);
}

void	turn_repeat(void *param, char c)
{
	t_all	*all;

	all = (t_all *)param;
	if (all->started_button == 0)
	{
		turn_press(param, c);
		all->start_time = ft_timestamp_milis(all);
		all->current_time = all->start_time;
		all->started_button = 1;
	}
	all->current_time = ft_timestamp_milis(all);
	if (all->current_time - all->start_time >= RENDER_INTERVAL)
	{
		turn_press(param, c);
		all->start_time = ft_timestamp_milis(all);
		all->current_time = all->start_time;
	}
}
